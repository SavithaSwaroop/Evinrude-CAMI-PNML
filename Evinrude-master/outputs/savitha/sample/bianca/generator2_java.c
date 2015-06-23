package fr.lip6.move.evinrude.generator;

import fr.lip6.move.evinrude.commons.model.petri.interfaces.IArc;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IModel;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.INode;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IPlace;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ITransition;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/**
 * Générateur de code pour la seconde version de BIANCA
 * @author Jean-Baptiste Voron
 */
public final class Generator2 {
        /**
         * Constructeur
         */
        private Generator2() {
        }

        /**
         * Generation du fichier de configuration de BIANCA
         * @param model Le modÚle complet
         * @param path dossier de l'application
         * @throws IOException En cas de problÚme
         */
        public static void generateNet(IModel model, String path) throws IOException {
                // Map<INode, String> variables = new HashMap<INode, String>();
                Set<String> events = new HashSet<String>();
                List<StringBuffer> postProcesses = new ArrayList<StringBuffer>();

                FileWriter writer = new FileWriter(path + "/generated/net.c", false);

                /* HEADER */
                writer.write("#include \"net.h\"\n\n");
                writer.write("/*********************************************************************************\n");
                writer.write(" * Détermine le marquage aprÚs le franchissement d'une transition sensible �  EVENT\n");
                writer.write(" */\n");
                writer.write("inline unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event) {\n\n");
                writer.write("  switch (current->place) {\n");

                /* Browse all model places */
                for (IPlace currentPlace : model.getPlaces()) {

                        if (currentPlace.getType() == IPlace.SPECIAL) {
                                continue;
                        }

                        writer.write("    /* Place " + currentPlace.getName() + " */\n");
                        writer.write("    case P" + currentPlace.getName().toUpperCase() + ": {\n");

                        /* ----------------------------------------------------- */
                        /* Create a new state if a STRUCT transition is detected */
                        boolean first = false;
                        for (INode outputTransition : currentPlace.getNext()) {
                                if (((ITransition) outputTransition).getType() == ITransition.STRUCTURAL) {
                                        if (!first) { writer.write("      state_t struct_state;\n"); first = true; }
                                        writer.write("      /* Duplique l'état courant du process (Pour la transition structurelle " + outputTransition.getName() + " */\n");
                                        writer.write("      struct_state = dup_state(*current);\n");
                                        // The .get(0) is possible since there is only one output place for the STRUCT transition
                                        writer.write("      struct_state.place = P" + outputTransition.getNext().get(0).getName().toUpperCase() + ";\n");
                                        writer.write("      add_state(process, struct_state);\n\n");
                                }
                        }
                        /* ----------------------------------------------------- */

                        /* ------------------------------------------------------------ */
                        /* Create a new state if a FUNCTION CALL transition is detected */
                        first = false;
                        for (INode outpoutTransition : currentPlace.getNext()) {
                                if (((ITransition) outpoutTransition).getType() == ITransition.FUNCTIONCALL) {
                                        if (!first) {
                                                writer.write("      state_t caller_state;\n");
                                                writer.write("      lresource_t path;\n");
                                                first = true;
                                        }
                                       
                                        ITransition caller = (ITransition) outpoutTransition;
                                        IPlace functionPath = null;
                                        IPlace functionEntry = null;

                                        // Look for the PATH place
                                        // TODO: The getNext should be able to sort the result in order to give only SPECIAL places
                                        for (INode next : caller.getNext()) {
                                                if (((IPlace) next).getType() == IPlace.PATH) {
                                                        functionPath = (IPlace) next;
                                                        break;
                                                }
                                        }

                                        // Look for the ENTRY function place
                                        // TODO: The getNext should be able to sort the result in order to give only SPECIAL places
                                        for (INode next : caller.getNext()) {
                                                if (((IPlace) next).getType() != IPlace.PATH) {
                                                        functionEntry = (IPlace) next;
                                                        break;
                                                }
                                        }

                                        // Check whether the functionEntry and functionPath are correctly set (!= null)
                                        if ((functionEntry == null) || (functionPath == null)) {
                                                break;
                                        }

                                        writer.write("      caller_state = dup_state(*current);\n\n");
                                        writer.write("      caller_state.place = P" + functionEntry.getName().toUpperCase() + ";\n\n");
                                        writer.write("      path.place = P" + functionPath.getName().toUpperCase() + ";\n");
                                        writer.write("      add_local_resource(&caller_state, path);\n");
                                        writer.write("      add_state(process, caller_state);\n");
                                }
                        }
                        /* ------------------------------------------------------------ */

                        /* ------------------------------------------------------------ */
                        /* Deal with function RETURN transitions (several input arcs) */
                        Map<INode, Integer> resources = new HashMap<INode, Integer>();
                        int countPred = 0; // Counter for preconditions
                        for (INode outpoutTransition : currentPlace.getNext()) {
                                if (((ITransition) outpoutTransition).getType() == ITransition.FUNCTIONRETURN) {
                                        for (INode pred : outpoutTransition.getPrevious()) {
                                                if (pred.equals(currentPlace)) {
                                                        continue;
                                                }
                                                if (resources.get(pred) == null) {
                                                        resources.put(pred, countPred++);
                                                }
                                        }
                                }
                        }

                        /* Dump all condition fetchings */
                        // TODO: Deal with global resources too !
                        for (INode condition : resources.keySet()) {
                                writer.write("      lresource_t* lresource" + resources.get(condition) + " = find_local_resource(current, P"
                                                + condition.getName().toUpperCase() + ");\n");
                        }

                        writer.write("\n");

                        for (INode outpoutTransition : currentPlace.getNext()) {
                                if (((ITransition) outpoutTransition).getType() == ITransition.FUNCTIONRETURN) {
                                        List<INode> TrueConditions = new ArrayList<INode>();
                                        List<INode> FalseConditions = new ArrayList<INode>();
                                        for (INode pred : outpoutTransition.getPrevious()) {
                                                if (pred.equals(currentPlace)) {
                                                        continue;
                                                }
                                                // Find the type of the arc between the transition and its predecessor
                                                if (model.getArc(pred.getName(), outpoutTransition.getName()).getType() == IArc.NORMAL) {
                                                        TrueConditions.add(pred);
                                                } else {
                                                        FalseConditions.add(pred);
                                                }
                                        }

                                        // Write the composed condition
                                        writer.write("      /* Transition " + outpoutTransition.getName() + " */\n");
                                        writer.write("      if (");
                                        for (INode c : TrueConditions) {
                                                writer.write("(lresource" + resources.get(c) + " != NULL) && ");
                                        }
                                        for (INode c : FalseConditions) {
                                                writer.write("(lresource" + resources.get(c) + " == NULL) && ");
                                        }
                                        writer.write("1) {\n");

                                        writer.write("        VERBOSE(\"Franchissement de la transition : " + outpoutTransition.getName() + "\\n\");\n");
                                        writer.write("        state_t return_state = dup_state(*current);\n\n");

                                        // Resource with normal arcs must be consumed
                                        // TODO: Deal with global resources too !
                                        for (INode c : TrueConditions) {
                                                writer.write("        /* On consomme la ressource (" + c.getName() + ") */\n");
                                                writer.write("        erase_local_resource(&return_state, lresource" + resources.get(c) + ",1);\n");
                                        }
                                        writer.write("\n        /* On change l'état... */\n");
                                        writer.write("        return_state.place = P" + outpoutTransition.getNext().get(0).getName().toUpperCase() + ";\n");
                                        writer.write("        add_state(process, return_state);\n");
                                        writer.write("      }\n\n");
                                }
                        }

                        /* ------------------------------------------------------------ */
                        /*
                         * Basic case: Deal with events
                         */
                        if (currentPlace.getNext().size() > 0) {
                                writer.write("      switch (event.type) {\n");
                               
                                /* Browse all output transitions */
                                for (INode outputTransition: currentPlace.getNext()) {
                                        ITransition nextTransition = (ITransition) outputTransition;
                                        String guard = nextTransition.getGuard();

                                        // If the current transition is structural or a function call or a function return... Skip (this case has been handled previously)
                                        if ((nextTransition.getType() == ITransition.STRUCTURAL) || (nextTransition.getType() == ITransition.FUNCTIONCALL) || (nextTransition.getType() == ITransition.FUNCTIONRETURN)) {
                                                continue;
                                        }

                                        /* If the transition produces several tokens (fork/thread)... It needs a post-treatment */
                                        /* This post-treatment is needed because information about new process/thread, is not known yet */
                                        if (nextTransition.getNext().size() > 1) {
                                                StringBuffer buf = new StringBuffer();
                                                buf.append("    /* Place " + currentPlace.getName().toUpperCase() + " */\n");
                                                buf.append("    case P" + currentPlace.getName().toUpperCase() + ": {\n");
                                                buf.append("      switch (event.type) {\n");
                                                buf.append("        case " + nextTransition.getGuard().toUpperCase() + ": {\n");
                                                buf.append("          process_t* newprocess = create_process(event.son);\n");
                                               
                                                // Look for the arc that carries the son identity
                                                INode sonCall = null;
                                                for (INode next : nextTransition.getNext()) {
                                                        if (model.getArc(nextTransition.getName(), next.getName()).getValuation().equals("son")) {
                                                                sonCall = next;
                                                                break;
                                                        }
                                                }

                                                buf.append("          state_t initial_state = create_state(P" + sonCall.getName().toUpperCase() + ");\n");
                                                buf.append("          add_state(newprocess, initial_state);\n");
                                                buf.append("          add_process(global_table, newprocess);\n");
                                                buf.append("          return;\n");
                                                buf.append("        }\n");
                                                buf.append("        default: return;\n");
                                                buf.append("      }\n");
                                                buf.append("    }\n");
                                                postProcesses.add(buf);
                                        }
                                       
                                        /* Standard case : An event is expected */
                                        writer.write("        case " + guard.toUpperCase() + ": {\n");

                                        /* Add the event to a list that is used for #define in event.h */
                                        events.add(nextTransition.getGuard().toUpperCase());

                                        /* If the current transition has several preconditions */
                                        if (nextTransition.getPrevious().size() > 1) {
                                                Map<INode, Integer> conditions = new HashMap<INode, Integer>();
                                                List<INode> TrueConditions = new ArrayList<INode>();
                                                List<INode> FalseConditions = new ArrayList<INode>();

                                                /* Browse all input places (preconditions) */
                                                int cptPreConditions = 0; // Counter for preconditions
                                                for (INode condition : nextTransition.getPrevious()) {
                                                        if (condition.equals(currentPlace)) {
                                                                continue;
                                                        }
                                                        // Add the condition to the list
                                                        conditions.put(condition, cptPreConditions);
                                                        writer.write("          process_t* coprocess" + cptPreConditions + " = find_process_state(global_table, P" + condition.getName().toUpperCase() + ");\n");
                                                        // Find the type of the arc between the transition and its predecessor
                                                        if (model.getArc(condition.getName(), nextTransition.getName()).getType() == IArc.NORMAL) {
                                                                TrueConditions.add(condition);
                                                        } else {
                                                                FalseConditions.add(condition);
                                                        }
                                                        cptPreConditions++;
                                                }
                                               
                                                // Write the composed condition
                                                writer.write("          if (");
                                                for (INode c : TrueConditions) {
                                                        writer.write("(coprocess" + conditions.get(c) + " != NULL) && ");
                                                }
                                                for (INode c : FalseConditions) {
                                                        writer.write("(coprocess" + conditions.get(c) + " == NULL) && ");
                                                }
                                                writer.write("1) {\n");

                                                // Resource with normal arcs must be consumed
                                                writer.write("              /* On consomme la ressource */\n");
                                                for (INode c : TrueConditions) {
                                                        writer.write("              erase_state(coprocess" + conditions.get(c) + ", find_state(coprocess" + conditions.get(c) + ", P" + c.getName().toUpperCase() + "));\n");
                                                }
                                                writer.write("               /* On change l'état... */\n");
                                                writer.write("              current->place = P" + nextTransition.getNext().get(0).getName().toUpperCase() + ";\n");
                                                writer.write("              return P" + currentPlace.getName().toUpperCase() + ";\n");
                                                writer.write("          }\n");

                                                // In case of only one output place
                                        } else {
                                                writer.write("          current->place = P" + nextTransition.getNext().get(0).getName().toUpperCase() + ";\n");
                                                writer.write("          return P" + currentPlace.getName().toUpperCase() + ";\n");
                                        }
                                        writer.write("        }\n");
                                }

                                // No default block is needed in case of STRUCT or CALLER or RETURN transition
                                writer.write("        default: return ERROR;\n");
                                writer.write("      }\n");
                        }
                        writer.write("    }\n\n");
                }

                writer.write("  }\n");
                writer.write("  assert(0);\n");
                writer.write("}\n\n\n");

                writer.write("/***************************************************************************\n");
                writer.write(" * Met �  jour le marquage aprÚs le franchissement d'aprÚs les informations récupérées\n");
                writer.write(" */\n");
                writer.write("inline void update(global_table_t* global_table, state_t* current, event_t event) {\n");
                writer.write("  switch (current->previous) {\n");

                for (StringBuffer post : postProcesses) {
                        writer.write(post.toString());
                }

                writer.write("    default: return;\n");
                writer.write("  }\n");
                writer.write("}\n\n");

                writer.close();

                /* ----------------------------------- */

                FileWriter writer2 = new FileWriter(path + "/generated/net.h", false);

                /* HEADER */
                writer2.write("#ifndef NET_H\n");
                writer2.write("#define NET_H\n\n");

                writer2.write("#include \"event.h\"\n");
                writer2.write("#include \"../process.h\"\n");
                writer2.write("#include \"../state.h\"\n");
                writer2.write("#include \"../global_table.h\"\n\n");

                writer2.write("inline unsigned int next(global_table_t* global_table, process_t* process, state_t* current, event_t event);\n");
                writer2.write("inline void update(global_table_t* global_table, state_t* current, event_t event);\n\n");

                writer2.write("/*************** GENERATED ***************/\n");
                /* Ecriture des symboles */
                int k = 1;
                for (IPlace p : model.getPlaces()) {
                        writer2.write("#define P" + p.getName().toUpperCase() + " " + k++ + "\n");
                }

                writer2.write("\n/** Pour le DEBUG **/\n");
                writer2.write("static const char* places[] = {\n");
                writer2.write("  \"\",\n");
                for (IPlace p : model.getPlaces()) {
                        writer2.write("  \"" + p.getName().toUpperCase() + "\",\n");
                }
                writer2.write("  \"\"\n");
                writer2.write("};\n\n");

                writer2.write("/*****************************************/\n\n");

                writer2.write("#endif /* end of include guard: " + model.getHead().getName().toUpperCase() + "_NET_H */\n\n");
                writer2.close();

                /* ----------------------------------- */

                FileWriter writer3 = new FileWriter(path + "/generated/event.h", false);

                /* HEADER */
                writer3.write("#ifndef EVENT_H\n");
                writer3.write("#define EVENT_H\n\n");

                writer3.write("#include \"../process.h\"\n\n");

                writer3.write("typedef struct {\n");
                writer3.write("  process_t* owner;\n");
                writer3.write("  int type;\n");
                writer3.write("  union {\n");
                writer3.write("    unsigned short son;\n");
                writer3.write("  };\n");
                writer3.write("} event_t;\n\n");

                writer3.write("/*************** GENERATED ***************/\n");
                /* Ecriture des symboles */
                k = 1;
                for (String e : events) {
                        writer3.write("#define " + e.toUpperCase() + " " + k++ + "\n");
                }

                writer3.write("\n/** Pour le DEBUG **/\n");
                writer3.write("static const char* events[] = {\n");
                writer3.write("  \"\",\n");
                for (String e : events) {
                        writer3.write("  \"" + e.toUpperCase() + "\",\n");
                }
                writer3.write("  \"\"\n");
                writer3.write("};\n\n");

                writer3.write("/*****************************************/\n\n");
                writer3.write("#endif /* End of include guard: " + model.getHead().getName().toUpperCase() + "_EVENT_H */\n\n");
                writer3.close();
        }
}

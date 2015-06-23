package fr.lip6.move.evinrude.commons.utils;

import fr.lip6.move.evinrude.commons.model.petri.ColoredVariable;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IArc;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IColorClass;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IPlace;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ISubModel;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ITransition;

import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 * Classe chargée de l'export de la représentation mémorie en CAMI
 * @author Jean-Baptiste Voron
 */
public final class CamiExport {
        /** Le compteur d'objets */
        private static int id;

        /** La table d'association des objets avec leur identifiant */
        private Map<String, Integer> objects;

        /** Constructeur */
        public CamiExport() {
                id = 2;
                this.objects = new HashMap<String, Integer>();
        }

        /**
         * Ajoute un objet �  la map des objet et lui associe un identifiant unique
         * @param name Le nom de l'objet �  ajotuer �  la map
         * @return le nouvel identifiant de l'objet
         */
        private int addObject(String name) {
                int newId = id++;
                this.objects.put(name, newId);
                return newId;
        }

        /**
         * Formatte une chaine de caractÚres au format CAMI
         * @param value La valeur �  convertir
         * @return La chaine au format CAMI
         */
        private String makeString(String value) {
                String newValue = value.replace('&', '_');
                return newValue.length() + ":" + newValue;
        }

        /**
         * Formatte une liste d'éléments avec un séparateur
         * @param s La liste d'éléments �  fusionner
         * @param delimiter Le délimiteur
         * @return La chaine de caratÚre fusionnée
         */
        private String join(Collection<String> s, String delimiter) {
                if (s.isEmpty()) { return ""; }
                Iterator<String> iter = s.iterator();
                StringBuffer buffer = new StringBuffer(iter.next());
                while (iter.hasNext()) { buffer.append(delimiter).append(iter.next()); }
                return buffer.toString();
        }

        /**
         * Exporte le sous-modÚle selectionné en commandes CAMI
         * @param model Le sous-modÚle �  convertir
         * @return Un ensemble de commandes CAMI
         */
        public String toCami(ISubModel model) {
                StringBuffer cami = new StringBuffer();

                // Parcours des places
                for (IPlace place : model.getPlaces()) {
                        int id = this.addObject(place.getName());
                        cami.append("CN(5:place,").append(id).append(")\n");
                        cami.append("CT(4:name,").append(id).append(",").append(this.makeString("State_" + place.getName())).append(")\n");
                        if (!place.getDomain().equals("")) {
                                cami.append("CT(6:domain,").append(id).append(",").append(this.makeString(place.getDomain())).append(")\n");
                        }
                        if (!place.getInitialMarking().equals("")) {
                                cami.append("CT(7:marking,").append(id).append(",").append(this.makeString(place.getInitialMarking())).append(")\n");
                        }
                }

                // Parcours des transitions
                for (ITransition transition : model.getTransitions()) {
                        int id = this.addObject(transition.getName());
                        cami.append("CN(10:transition,").append(id).append(")\n");
                        cami.append("CT(4:name,").append(id).append(",").append(this.makeString(transition.getName())).append(")\n");
                        if (!transition.getGuard().equals("")) {
                                cami.append("CT(5:guard,").append(id).append(",").append(this.makeString(transition.getGuard())).append(")\n");
                        }
                }

                // Parcours des arcs
                for (IArc arc : model.getArcs()) {
                        int id = this.addObject(arc.getSource().getName() + "," + arc.getTarget().getName());
                        cami.append("CA(3:arc,");
                        cami.append(id).append(",");
                        cami.append(this.objects.get(arc.getSource().getName())).append(",");
                        cami.append(this.objects.get(arc.getTarget().getName())).append(")\n");
                        if (!arc.getValuation().equals("1")) {
                                cami.append("CT(9:valuation,").append(id).append(",").append(this.makeString(arc.getValuation())).append(")\n");
                        }
                }

                // En-Tête du fichier
                cami.append("CN(3:net,1)\n");

                // Calcul des entetes du modele
                if (model.getColorClasses().size() > 0) {
                        cami.append("CM(11:declaration,1,1,-1,5:Class)\n");
                }

                int n = 2;
                for (IColorClass colorClass : model.getColorClasses()) {
                        cami.append("CM(11:declaration,1,").append(n++).append(",2,");

                        StringBuffer colorClassDesc = new StringBuffer();
                        colorClassDesc.append(colorClass.getName()).append(" is [");

                        if (colorClass.getType() == IColorClass.RANGE) {
                                List<String> values = colorClass.getValues();
                                colorClassDesc.append(values.get(0)).append("..").append(values.get(values.size() - 1));
                        } else {
                                colorClassDesc.append(this.join(colorClass.getValues(), ","));
                        }
                        colorClassDesc.append("];");
                        cami.append(this.makeString(colorClassDesc.toString())).append(")\n");
                }

                if (model.getVariables().size() > 0) {
                        cami.append("CM(11:declaration,1," + n++ + ",-1,3:Var)\n");
                }

                // Calcul de la declaration des variables
                for (ColoredVariable cVar : model.getVariables()) {
                        cami.append("CM(11:declaration,1,").append(n++).append(",2,");

                        StringBuffer cVarDesc = new StringBuffer();
                        cVarDesc.append(cVar.getName()).append(" in ").append(cVar.getColorClass()).append(";");
                        cami.append(this.makeString(cVarDesc.toString())).append(")\n");
                }

                return cami.toString();
        }

}

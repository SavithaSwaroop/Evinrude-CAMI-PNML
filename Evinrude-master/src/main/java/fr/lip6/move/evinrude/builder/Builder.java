package fr.lip6.move.evinrude.builder;

import fr.lip6.move.evinrude.builder.perspectives.struct.StructuralPerspective;
import fr.lip6.move.evinrude.commons.exceptions.EvinrudeException;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IApplication;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IBlock;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.ICfg;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IExecutable;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IFunction;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IInstruction;
import fr.lip6.move.evinrude.commons.model.petri.Model;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IModel;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ISubModel;
import fr.lip6.move.evinrude.commons.utils.log.EvinrudeLogFormatter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.ServiceLoader;
import java.util.Set;
import java.util.logging.Logger;

/**
 * Cette classe est responsable de la construction du rÃ©seau de petri en utilisant un systÃ¨me de perspectives.<br>
 * Les perspectives sont chargÃ©s Ã  l'aide du ServiceLoader de java.
 *
 * @author ClÃ©ment DÃ©moulins
 * @author Jean-Baptiste Voron
 */
/**
 * This class is responsible for the construction of the Result © petri bucket using a system will prospects. <br>
 * The outlook is loaded Ã © s using the java ServiceLoader .
 *
 * @ Author ClÃ © ment DÃ © mills
 * @ Author Jean-Baptiste Voron
 * @author sneeth
 *
 */
public class Builder {
	/** Le logger */
	private static Logger LOG = Logger.getLogger(Builder.class.getName());

	/** L'application en cours de traitement */
	private IApplication application;

	/** Le modÃ¨le de l'application */
	/** The model of the application */
	private IModel model;

	/** Gestionnaire des rÃ©sultats rÃ©initialiser pour chaque CFG */
	private ResultManager resultManager;

	/** Gestion particuliÃ¨re pour les IRuleExecutable qui ne doivent Ãªtre traitÃ©es qu'une fois pour tous les CFGÂ de l'exÃ©cutable */
	/** Management particular for the Iruleexecutable which must be treated as that time for all the CFGs of executable*/
	private Map<IRuleExecutable, ResultEntry> ruleExecutables;

	/** Liste des perspectives chargÃ©es */
	private List<IPerspective> perspectives;

	/**
	 * Constructeur
	 * @param application L'application en cours de construction
	 */
	public Builder(IApplication application) {
		this.application = application;
		this.perspectives = getPerspectives();
	}

	/**
	 * Chargement des perspectives.
	 * @return la liste des perspectives disponible.
	 *  Loading perspectives.
	 	*return The list of available perspectives 
	 */
	public final List<IPerspective> getPerspectives() {
		List<IPerspective> perspectives = new ArrayList<IPerspective>();

		// Chargement de la perspective structurelle
		perspectives.add(new StructuralPerspective());

		// Chargement des perspectives Ã  l'aide du ServiceLoader de java
		ServiceLoader<IPerspective> loader = ServiceLoader.load(IPerspective.class);
		for (IPerspective perspective : loader) {
			LOG.info("Perspective " + perspective.getName() + " loaded !");
			perspectives.add(perspective);
		}

		// VÃ©rification des dÃ©pendances, si une dÃ©pendance ne peut pas Ãªtre satisfaite on quitte
		Set<String> deps = new HashSet<String>();
		for (IPerspective perspective : perspectives) {
			deps.add(perspective.getName());
			for (IRule rule : perspective.getRules()) {
				deps.add(rule.getName());
			}
		}
		for (IPerspective perspective : perspectives) {
			if (!deps.containsAll(perspective.getDependencies())) {
				LOG.severe("Dependency not satisfied in perspective : " + perspective.getName());
				System.exit(1);
			}
			for (IRule rule : perspective.getRules()) {
				if (!deps.containsAll(rule.getDependencies())) {
					LOG.severe("Dependency not satisfied in rule : " + rule.getName());
					System.exit(1);
				}
			}
		}

		return perspectives;
	}

	/**
	 * Traite une liste de rÃ¨gles en gÃ©rant les dÃ©pendances.<br>
	 * Ã€ la fin de cette mÃ©thode le rÃ©seau de Petri est complÃ©tÃ© en fonction du CFG et des rÃ¨gles passÃ©es en paramÃ¨tres.
	 *
	 * @param executable executable
	 * @param cfg CFG sur lequel les rÃ¨gles doivent Ãªtre appliquÃ©es
	 * @param rules rÃ¨gles Ã  traiter
	 * @throws EvinrudeException Erreur du modÃ¨le
	 * * Process a list of rules managing dependencies. <br>
* At the end of this method the Petri net is completed based on the CFG and passed as parameters rules.
*dropoff window
*param Executable executable
*param Cfg CFG on which the rules must be applied
*param Rules rules to deal
*throws EvinrudeException Error Model
*A reference IExecutable hand function and a cfg list and is executable
	 */
	private void process(IExecutable executable, ICfg cfg, List<IRule> rules) throws EvinrudeException {
		List<IRule> notProcessed = new ArrayList<IRule>(rules);

		while (!notProcessed.isEmpty()) {
			// CrÃ©ation de la liste des rÃ¨gles pouvant Ãªtre traitÃ©
			// Create a list of rules that can be processed
			List<IRule> toProcess = new ArrayList<IRule>(notProcessed);
			LOG.finer("Not processed : " + toProcess);
			for (IRule rule : notProcessed) {
				
				for (String dep : rule.getDependencies()) {
					//LOG.info("builder:dep :" + dep);
					if (!resultManager.containsDepenpency(dep)) {
						LOG.info("builder:removerule :" + dep);
						toProcess.remove(rule);
					}
				}
			}

			// Impossible de faire passer les rÃ¨gles, il y a un problÃ¨me de dÃ©pendance
			//// Can not pass the rules, there is a dependency problem
			if (toProcess.isEmpty()) {
				throw new EvinrudeException("Can't resolv dependencies !");
			}

			// Traitement de la liste de rÃ¨gles
			//// Process the list of rules
			for (IRule rule : toProcess) {
				LOG.info("Builder:procesing the list of rules:step1");
				LOG.finer("Processing rule [" + rule.getName() + "] on " + cfg.getFileName());
				EvinrudeLogFormatter.getInstance().increaseIndent();

				ResultEntry resultEntry;

				// RÃ©sultats des dÃ©pendances de la rÃ¨gle en cours de traitement
				// Results dependencies of the rule being processed
				ResultDep depenpencies = resultManager.getResultDep(rule);

				// Sous modÃ¨les Ã  vÃ©rifier
				// Under Templates check
				Set<ISubModel> toCheck = new HashSet<ISubModel>();

				// Traitement de l'executable si il n'a pas dÃ©jÃ  Ã©tÃ© traitÃ©
				// Process the executable if it has not already been processed
				if (rule instanceof IRuleExecutable) {
					LOG.info("Builder:procesing the list of rules:step2");
					resultEntry = ruleExecutables.get(rule);
					if (resultEntry == null) {
						LOG.info("Builder:procesing the list of rules:step3");
						LOG.finer("    Traitement de " + rule.getName() + " sur executable : " + executable.getName());
						resultEntry = new ResultEntry(rule, executable, ((IRuleExecutable) rule).process(depenpencies, executable));
						ruleExecutables.put((IRuleExecutable) rule, resultEntry);
						LOG.info("Builder:procesing the list of rules:step4");
					}
					if (resultEntry == null) 
					{
						LOG.info("Builder:its empty");
					}
					toCheck.addAll(resultEntry.getSubModels());
					LOG.info("Builder:procesing the list of rules:step5");
					resultManager.putResult(rule, executable, resultEntry);
					LOG.info("Builder:procesing the list of rules:step6");
				}

				// Traitement du CFG
				// Process the CFG
				if (rule instanceof IRuleCfg) {
					LOG.finer("    Traitement de treatment" + rule.getName() + " sur CFG : " + cfg.getName());
					resultEntry = new ResultEntry(rule, cfg, ((IRuleCfg) rule).process(depenpencies, cfg));
					toCheck.addAll(resultEntry.getSubModels());
					resultManager.putResult(rule, cfg, resultEntry);
					LOG.info("Builder:procesing the list of rules:step7");
					
				}

				for (IFunction func : cfg.getFunctions()) {
					// Traitement de la fonction
					if (rule instanceof IRuleFunction) {
						LOG.info("Builder:procesing the list of rules:step8");
						LOG.finer("    Traitement de " + rule.getName() + " sur function : " + func.getName());
						resultEntry = new ResultEntry(rule, func, ((IRuleFunction) rule).process(depenpencies, func));
						toCheck.addAll(resultEntry.getSubModels());
						resultManager.putResult(rule, func, resultEntry);
					}
					for (IBlock block : func.getBlocks()) {
						// Traitement du block
						if (rule instanceof IRuleBlock) {
							LOG.finer("    Traitement de " + rule.getName() + " sur block : " + block.getId());
							resultEntry = new ResultEntry(rule, block, ((IRuleBlock) rule).process(depenpencies, block));
							toCheck.addAll(resultEntry.getSubModels());
							resultManager.putResult(rule, block, resultEntry);
							LOG.info("Builder:procesing the list of rules:step9");
						}
						// Traitement des instructions
						if (rule instanceof IRuleInstruction) {
							// Cas particulier lorsqu'il n'y a pas d'instructions
							// Special case when there is no instruction
							if (block.getInstructions().isEmpty()) {
								// RÃ©sultat vide
								resultEntry = new ResultEntry(rule, new Object(), new ArrayList<ISubModel>());
								resultManager.putResult(rule, resultEntry.getCfgObj(), resultEntry);
								LOG.info("Builder:procesing the list of rules:step10");
							}
							for (IInstruction instruction : block.getInstructions().values()) {
								LOG.finest("    Traitement de " + rule.getName() + " sur l'instruction : " + instruction.getCfgLine());
								resultEntry = new ResultEntry(rule, instruction, ((IRuleInstruction) rule).process(depenpencies, instruction));
								toCheck.addAll(resultEntry.getSubModels());
								resultManager.putResult(rule, instruction, resultEntry);
								LOG.info("Builder:procesing the list of rules:step11");
								
							}
						}
					}
				}

				// VÃ©rification des propriÃ©tÃ©s de la rÃ¨gle pour tous les sous-modÃ¨les (locales)
				// Verify the rule properties for all sub-models (local)
				for (ISubModel subModel : toCheck) {
					LOG.info("Builder:procesing the list of rules:step1222");
					for (IProperty property : rule.getProperties()) {
						LOG.info("Builder:procesing the list of rules:step12");
						if (!property.check(subModel)) {
							LOG.severe("Local property " + property.getName() + " has failed !");
							System.exit(1);
						}
					}
				}
				
				
			

				// La rÃ¨gle est marquÃ©e comme traitÃ©e
				// The rule is marked as processed
				notProcessed.remove(rule);

				EvinrudeLogFormatter.getInstance().decreaseIndent();
			}
		}
	}

	/**
	 * Construction d'un rÃ©seau de Petri Ã  partir de la reprÃ©sentation de son CFG.<br>
	 *
	 * @param executable Le rÃ©seau de Petri sera construit pour cet executable
	 * @return RÃ©seau de Petri construit
	 * @throws EvinrudeException Erreur du modÃ¨le
	 * / **dropoff window
* Construction of a Petri net from the representation of its CFG. <br>
*dropoff window
*param The executable Petri net will be built for this executable
*return Petri Nets built
*throws EvinrudeException Error Model
* /dropoff window
	 */
	public final IModel process(IExecutable executable) throws EvinrudeException {
		LOG.info("Build application " + application.getName());
		EvinrudeLogFormatter.getInstance().increaseIndent();

		LOG.info("Processing executable " + executable.getName());
		EvinrudeLogFormatter.getInstance().increaseIndent();

		// CrÃ©ation du model
		//// Create the model  Can't resolv dependencies
		model = new Model(executable);
		ruleExecutables = new HashMap<IRuleExecutable, ResultEntry>();

		// Liste des propriÃ©tÃ©s globales Ã  vÃ©rifier sur le modÃ¨le en fin de traitement
		// List of global properties to check on the model at the end of treatment
		List<IProperty> properties = new ArrayList<IProperty>();
		LOG.info("builder1 ");
		
		// Tant qu'il y a des CFG Ã  traiter, sachant que les traitements peuvent ajouter de nouveaux CFG.
		// As long as there has CFG to deal with, knowing that treatments can add new CFG.
		while (model.hasNextNewCfg()) {
			LOG.info("builder2 ");
			ICfg cfg = model.nextNewCfg();
			LOG.fine("Processing cfg " + cfg.getName());
			EvinrudeLogFormatter.getInstance().increaseIndent();

			// Initialisation du gestionnaire de rÃ©sultat
			// Initialize the result handler
			resultManager = new ResultManager(executable, perspectives);

			// Traitement de toutes les rÃ¨gles des perspectives
			// Process all rules prospects
			List<IRule> rules = new ArrayList<IRule>();
			for (IPerspective perspective : perspectives) {
				rules.addAll(perspective.getRules());
				properties.addAll(perspective.getProperties());

			}
			process(executable, cfg, rules);
			EvinrudeLogFormatter.getInstance().decreaseIndent();
		}

		// VÃ©rification des propriÃ©tÃ©s globales
		// Check global properties
		for (IProperty property : properties) {
			LOG.info("builder3 ");
			if (!property.check(model)) {
				LOG.severe("Property " + property.getName() + " fail !");
				System.exit(1);
			}
		}

		EvinrudeLogFormatter.getInstance().decreaseIndent();
		LOG.info("End processing executable " + executable.getName());

		EvinrudeLogFormatter.getInstance().decreaseIndent();
		LOG.info("End processing application " + application.getName());
		LOG.info("End MODEL : " + model.toString());
		
		
	return model;
	}
}

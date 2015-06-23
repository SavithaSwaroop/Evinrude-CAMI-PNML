package fr.lip6.move.evinrude.builder;

import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IExecutable;
import fr.lip6.move.evinrude.commons.utils.CamiExport;
import fr.lip6.move.evinrude.commons.utils.DotExport;
import fr.lip6.move.evinrude.commons.utils.PNMLExport;
import fr.lip6.move.pnml.framework.general.PnmlExport;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

import fr.lip6.move.evinrude.commons.exceptions.*;

//import org.eclipse.emf.ecore.EObject;

/**
 * @author ClÃ©ment DÃ©moulins
 * @author Jean-Baptiste Voron
 */
public class ResultManager {
	/** Le logger */
	private static Logger LOG = Logger.getLogger(ResultManager.class.getName());

	/**
	 * Structure indexant les rÃ©sultats en fonction de l'Ã©lÃ©ment du CFG utilisÃ© pour gÃ©nÃ©rer ce rÃ©sultat
	 * ainsi que du nom de la rÃ¨gle ayant gÃ©nÃ©rÃ© ce rÃ©sultat.
	 */
	private final Map<String, Map<Object, ResultEntry>> repository = new HashMap<String, Map <Object, ResultEntry>>();

	private IExecutable executable;

	private List<IPerspective> perspectives;

	/**
	 * Constructor
	 * @param executable executable
	 * @param perspectives liste des perspectives Ã  gÃ©rer
	 */
	public ResultManager(IExecutable executable, List<IPerspective> perspectives) {
		this.executable = executable;
		this.perspectives = new ArrayList<IPerspective>(perspectives);
	}

	/**
	 * Permet de rÃ©cupÃ©rer un ResultDep contenant les rÃ©sultats de tous les rÃ©sultats des
	 * dÃ©pendances de la rÃ¨gle passÃ© en paramÃ¨tre.
	 * @param rule rÃ¨gle concernÃ©
	 * @return objet contenant les rÃ©sultats
	 */
	public final ResultDep getResultDep(IRule rule) {
		ResultDep resultDep = new ResultDep(executable);

		// Si il n'y a pas de dependence
		if (rule.getDependencies() == null || rule.getDependencies().isEmpty()) {
			return resultDep;
		}

		// On ajoute les rÃ©sultats de chaque dÃ©pendances
		for (String dep : rule.getDependencies()) {
			Map<Object, ResultEntry> depResult = repository.get(dep);
			if (depResult == null) {
				LOG.severe("Dependency [" + rule.getName() + " -> " + dep + "] not satisfied !");
				throw new IllegalArgumentException("Error in dependency tree, caused by the rule '" + rule + "'");
			}
			for (Object cfgObj : depResult.keySet()) {
				ResultEntry result = depResult.get(cfgObj);
				resultDep.putResultEntry(cfgObj, result);
				
			}
		}

		return resultDep;
	}

	/**
	 * Permet d'ajouter un rÃ©sultat au gestionnaire
	 * @param rule rÃ¨gle ayant gÃ©nÃ©rÃ© ce rÃ©sultat
	 * @param cfgElement Ã©lÃ©ment du CFG concernÃ© par le rÃ©sultat
	 * @param result rÃ©sultat
	 */
	public final void putResult(IRule rule, Object cfgElement, ResultEntry result) {
		Map<Object, ResultEntry> ruleResults = repository.get(rule.getName());
		if (ruleResults == null) {
			ruleResults = new HashMap<Object, ResultEntry>();
		}
		ruleResults.put(cfgElement, result);
		repository.put(rule.getName(), ruleResults);
		checkEndOfPerspectives();
	}

	/**
	 * Export le model courrant lorsqu'une perspective a traitÃ© toutes ses rÃ¨gles
	 */
	private void checkEndOfPerspectives() {
		for (IPerspective perspective : new ArrayList<IPerspective>(perspectives)) {
			boolean isEnded = true;
			for (IRule rule : perspective.getRules()) {
				if (!repository.containsKey(rule.getName())) {
					isEnded = false;
					break;
				}
			}
			if (isEnded) {
				
				LOG.info("main:builder:into dump");
				DotExport.dumpDotRepresentation(executable.getModel(), perspective.getName().toLowerCase(), executable.getFolder());
				CamiExport.dumpcamiRepresentation(executable.getModel(), perspective.getName().toLowerCase(), executable.getFolder());
			//	PnmlExport.exportObject((EObject)executable.getModel(), executable.getFolder());
				LOG.info("main:builder:into dumppnml");
			/*	try{
				PNMLExport.dumpPNMLRepresentation(executable.getModel(), perspective.getName().toLowerCase(), executable.getFolder());
				}
				catch(Exception e){
					LOG.info("error");
					}*/
				perspectives.remove(perspective);
			}
		}
	}

	/**
	 * @param dependency dÃ©pendance Ã  vÃ©rifier
	 * @return <code>true</code> si le gestionnaire possÃ¨de des rÃ©sultats associÃ©s Ã  cette dÃ©pendance
	 */
	public final boolean containsDepenpency(String dependency) {
		return repository.containsKey(dependency);
	}
}

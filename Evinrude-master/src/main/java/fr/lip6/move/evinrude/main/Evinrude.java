package fr.lip6.move.evinrude.main;

import fr.lip6.move.evinrude.builder.Builder;
import fr.lip6.move.evinrude.builder.Flattener;
import fr.lip6.move.evinrude.commons.exceptions.EvinrudeException;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IApplication;
import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IExecutable;
import fr.lip6.move.evinrude.commons.utils.CamiExport;
import fr.lip6.move.evinrude.commons.utils.DotExport;
import fr.lip6.move.evinrude.commons.utils.PNMLExport;
import fr.lip6.move.evinrude.commons.utils.StatsExport;
import fr.lip6.move.evinrude.commons.utils.log.ConsoleHandler;
import fr.lip6.move.evinrude.commons.utils.log.EvinrudeLogFormatter;
import fr.lip6.move.evinrude.commons.utils.log.EvinrudeLogHandler;
import fr.lip6.move.evinrude.generator.Generator;
import fr.lip6.move.evinrude.optimizer.IReduction;
import fr.lip6.move.evinrude.optimizer.Reducer;
import fr.lip6.move.evinrude.parser.IFile;
import fr.lip6.move.evinrude.parser.Parser;
import fr.lip6.move.pnml.framework.utils.exception.InvalidIDException;
import fr.lip6.move.pnml.framework.utils.exception.VoidRepositoryException;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;
import java.util.logging.LogManager;
import java.util.logging.Logger;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.GnuParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.OptionBuilder;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;

/**
 * Classe principale du projet <b>Evinrude</b>
 * @author Jean-Baptiste Voron
 * @author Clément Démoulins
 */
public final class Evinrude {
	/** Le logger */
	private static Logger LOG;

	/** Constructeur privé */
	private Evinrude() { }
	


	/**
	 * Entrée principale du module <b>builder</b> du projet<br>
	 * Les paramètres nécessaires sont les suivants :
	 * <ul>
	 * <li>Une indication sur le traitement à effectuer</li>
	 * <li>Le répertoire où sont stockés les CFG de l'application</li>
	 * </ul>
	 * @param args Les arguments fourni au programme en ligne de commande
	 * @throws EvinrudeException Erreur lors de l'éxecution d'evinrude
	 * @throws IOException erreur d'entrée/sortie
	 * @throws InterruptedException inturreption alors que j'attends la fin de l'execution d'une commande
	 * @throws ParseException Erreur lors de l'analyse des arguments
	 */
	
	
	/**dropoff window
	* Main entrance of the module <b> builder </ b> of <br> Project
	* The parameters required are:
	* <Ul>
	* <Li> An indication of the operation to perform </ li>
	* <Li> The directory that stores CFG application </ li>
	* </ Ul>
	*param Args The arguments supplied to the command line program
	*throws EvinrudeException Error in the actual execution of evinrude
	*throws IOException input / output error
	*throws InterruptedException inturreption as I wait for the end of the execution of an order
	*throws ParseException Error analysis of the arguments
	 * @throws VoidRepositoryException 
	 * @throws InvalidIDException 
	*/
	
	
	public static void main(String[] args) throws EvinrudeException, IOException, InterruptedException, ParseException, InvalidIDException, VoidRepositoryException {
		// Option command line
		// Option de la ligne de commande
		Options options = new Options();
		OptionBuilder.withArgName("path name");
		OptionBuilder.hasArgs(2);
		OptionBuilder.withValueSeparator(' ');
		OptionBuilder.withDescription("Analyze a local application");
		options.addOption(OptionBuilder.create("analyze"));
		options.addOption("benchs", false, "Use the application's repository");
		options.addOption("negate", false, "In benchs mode, remove the argument of the applications proccess list");
		options.addOption("config", true, "Configuration file, defaut use resources/config.properties");

		GnuParser gnuParser = new GnuParser();
		CommandLine cli = gnuParser.parse(options, args);

		// Initialisation
		//String configFilePath = "C:\\Evinrude\\Evinrude-master\\resources\\config.properties";
		String configFilePath = "resources/config.properties";
		if (cli.hasOption("config")) {
			configFilePath = cli.getOptionValue("config");
		}
		initializeLogger(configFilePath);
		LOG.config("Starting Evinrude : << Failure is always between the chair and the screen >>");
		initializeProperties(configFilePath);

		// ————————————————————————————————————————————
		// ** 1 **  Chargement des applications
		// ** 1 ** Load applications
		EvinrudeLogFormatter.getInstance().setState("P");
		LOG.info("Step 1 : Load applications sources");
		Parser parser = new Parser();
		Iterator<IApplication> apps;

		//    1.a ** Using the deposit benchs
		File benchsResult = new File(System.getProperty("evinrude.outputdir"), "benchs.result");
		if (cli.hasOption("benchs")) {
			if (benchsResult.exists()) { benchsResult.delete(); }
			apps = parser.parseBenchs(Arrays.asList(cli.getArgs()), cli.hasOption("negate"));

		//    1.b ** Utilisation de sources locales
//		    1.b **	Using local sources
		} else if (cli.hasOption("analyze")) {
			// Récupération du répertoire contenant tous les fichiers XML contenant la description du CFG
			// Retrieving directory containing all XML files containing the description of CFG
			String inputvalues=cli.getOptionValues("analyze")[0];
			LOG.info("cli.getoptionvalues(analyze0):"+inputvalues);
			List<IFile> files = Browser.buildFileList(cli.getOptionValues("analyze")[0]);
			//String inputvalues1=cli.getOptionValues("analyze")[1];
			//LOG.info("cli.getoptionvalues(analyze0):"+inputvalues1);
			LOG.info("main:step1");
			apps = Collections.singletonList(parser.parse(cli.getOptionValues("analyze")[1], files.iterator())).iterator();
			LOG.info("main:step2");
		//    1.c ** Erreur dans les arguments
			//1.c ** Error in arguments Clement Desmoulinstoutes the information contained in the CFG
		} else {
			new HelpFormatter().printHelp("evinrude", "", options, "One of the two options : -analyze|-benchs must be selected");
			return;
		}

		// Pour chaque application on lance le processus de construction de l'IDS//
		// For each application you launch the IDS building process
		while (apps.hasNext()) {
			LOG.info("main:step3");
			EvinrudeLogFormatter.getInstance().setState("P");
			IApplication app = apps.next();

			Builder builder = new Builder(app);
			Reducer reducer = new Reducer(app);
			Flattener flattener = new Flattener();
			Generator generator = new Generator(app);
			fr.lip6.move.evinrude.compiler.Compiler compiler = new fr.lip6.move.evinrude.compiler.Compiler();

			for (IExecutable executable : app.getExecutables()) {

				// ————————————————————————————————————————————
				// ** 2 **  Construction du réseaux de Petri
				//// ** 2 ** Petri nets Construction
				EvinrudeLogFormatter.getInstance().setState("B");//i m here
				builder.process(executable);
				LOG.info("main:builder:step4");
				//  2.5 ** Réduction hiérarchique
				//// 2.5 ** hierarchical Reduction
				EvinrudeLogFormatter.getInstance().setState("RH");
				reducer.reduc(executable, IReduction.HIERARCHICAL);
								
				LOG.info("main:builder:step5");
				//  2.9 **  Dump de contrôle dans un fichier DOT
				//// 2.9 ** Control Dump in a DOT file
				DotExport.dumpDotRepresentation(executable.getModel(), "pre-flatten", executable.getFolder());
				CamiExport.dumpcamiRepresentation(executable.getModel(), "pre-flatten", executable.getFolder());
		//		PNMLExport.dumpPNMLRepresentation(executable.getModel(), "pre-flatten", executable.getFolder());
				// ————————————————————————————————————————————
				// ** 3 **  Aplatissement des réseaux de Petri
				//// ** 3 ** Flattening of Petri nets
				EvinrudeLogFormatter.getInstance().setState("F");
				flattener.flatten(executable);
							
				LOG.info("main:builder:step6");
				//  3.5 ** Réduction non hiérarchique
				//// 3.5 ** nonhierarchical Reduction
				EvinrudeLogFormatter.getInstance().setState("RF");
				reducer.reduc(executable, IReduction.FLAT);
				
				
				LOG.info("main:builder:step7");
				//  3.9 **  Dump de contrôle dans un fichier DOT
				//// 3.9 ** Control Dump in a DOT file
				DotExport.dumpDotRepresentation(executable.getModel(), "final", executable.getFolder());
				CamiExport.dumpcamiRepresentation(executable.getModel(), "final", executable.getFolder());
			//	PNMLExport.dumpPNMLRepresentation(executable.getModel(), "final", executable.getFolder());
				LOG.info("main:builder:step8");
				// ————————————————————————————————————————————
				// ** 4 ** Génération de code (RdP dans Bianca)
				// ** 4 ** Code Generation (MOP in Bianca)
			//	EvinrudeLogFormatter.getInstance().setState("G");
			//	generator.generateNets(executable);
				LOG.info("main:builder:step9");
//processing the list of rules
				// ————————————————————————————————————————————
				// ** 5 ** Compilation et tests de bianca
				//// ** 5 ** Compilation and bianca tests comment from here
				/*EvinrudeLogFormatter.getInstance().setState("C");
				LOG.info("compile:executable is :" + executable.getName());
				int result = compiler.compile(executable);
				LOG.info("main:builder:step10");
				String resultString = "OK";
				if (result != 0) {
					resultString = "KO";
				}

				if (cli.hasOption("benchs")) {
					boolean result2 = false;
					if (result == 0) {
						LOG.info("Test IDS for " + executable.getApplication().getName() + "/" + executable.getName());
						EvinrudeLogFormatter.getInstance().increaseIndent();
						result2 = testIDS(executable);
						EvinrudeLogFormatter.getInstance().decreaseIndent();
					}
					String resultString2 = "OK";
					if (!result2) {
						resultString2 = "KO";
					}
					LOG.info("main:builder:step11");
					// Écriture du tableau de bord (fichier 'benchs.result')
					BufferedWriter writer = new BufferedWriter(new FileWriter(benchsResult, true));
					writer.append(String.format("%-50s %s %s", app.getName() + "/" + executable.getName(), resultString, resultString2));
					writer.newLine();
					writer.close();
				}*/// till here comment it
				LOG.info("main:builder:step12");
				// Permettre au GC de faire son boulot
				// Allow the GC to do its job
				executable.setModel(null);
			}
		//StatsExport.dumpStats(app, new File(System.getProperty("evinrude.outputdir") + "/" + app.getName()));
		}
	}

	/**
	 * Recupère les traces disponibles sur le dépôt puis les tests sur l'IDS généré pour cet executable
	 * @param executable executable
	 * @return résultat du test, <code>true</code> si toutes les traces sont passées <code>false</code> sinon
	 */
	/**
	 * Retrieves the tracks available on the deposit and the tests on the IDS generated for the executable
	 * @param executable
	 * @return Test result, <code > true </ code> if all traces are passed <code > false </ code> if
	 */
	private static boolean testIDS(IExecutable executable) {
		File replay = new File(executable.getBiancaFolder() + "/replay");
		if (!replay.isFile()) {
			LOG.warning("replay executable doesn't exist in [" + executable.getBiancaFolder() + "]");
			return false;
		} else if (!replay.canExecute()) {
			LOG.warning("replay is not executable [" + executable.getBiancaFolder() + "]");
			return false;
		}

		// Pour chaque trace on test l'IDS
		Iterator<IFile> iterator = Browser.findIDSTrace(executable);
		while (iterator.hasNext()) {
			IFile trace = iterator.next();
			String[] split = trace.getFilename().split("\\.");
			int resultExpected = Integer.valueOf(split[split.length - 2]);

			LOG.fine("Test de la trace : " + trace.getFilename());
			EvinrudeLogFormatter.getInstance().increaseIndent();
			try {
				// Création d'un fichier temporaire
				File traceFile = File.createTempFile(trace.getFilename(), "" + System.currentTimeMillis());
				traceFile.deleteOnExit();

				// Copie de la trace dans un fichier temporaire
				BufferedInputStream bis = new BufferedInputStream(trace.getInputStream());
				BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(traceFile));
				int c;
				while ((c = bis.read()) != -1) {
					bos.write(c);
				}
				bis.close();
				bos.close();

				try {
					// Lancement du test de l'IDS
					// IDS test launch
					ProcessBuilder pb = new ProcessBuilder(replay.getAbsolutePath(), traceFile.getAbsolutePath());
					Process replayProcess = pb.start();
					int result = replayProcess.waitFor();

					// Résultat du test
					if (result != resultExpected) {
						LOG.warning("Test with trace '" + trace.getFilename() + "' failed, expected: " + resultExpected + " returned: " + result);
						return false;
					} else {
						LOG.fine("\tsucceed");
					}
				} catch (InterruptedException e) {
					LOG.warning("replayProcess interrupted : " + e.getMessage());
				}
			} catch (IOException e) {
				LOG.warning("Impossible de créer le fichier temporaire pour les traces [" + e.getMessage() + "]");
			}
			EvinrudeLogFormatter.getInstance().decreaseIndent();
		}
		return true;
	}

	/**
	 * Initialisation du logger
	 * @throws IOException Problème de chargement des propriétés du logger
	 * @param configFilePath Fichier de configuration à utiliser
	 */
	/**
	 * Initialize the logger
	 * @param configFilePath configuration file to use
	 * @throws IOException Problem loading properties logger
	 */
	private static void initializeLogger(String configFilePath) throws IOException {
		// Chargement des propriétés du logger
		InputStream is = new FileInputStream(configFilePath);
		LogManager.getLogManager().readConfiguration(is);
		is.close();

		LOG = Logger.getLogger("fr.lip6.move.evinrude"); //$NON-NLS-1$
		LOG.setUseParentHandlers(false);

		// Les logs sont affiches dans la console
		LOG.addHandler(new ConsoleHandler());

		// Les logs sont enregistres dans un fichier.
		try {
			EvinrudeLogHandler handler = EvinrudeLogHandler.getInstance();
			EvinrudeLogFormatter format = EvinrudeLogFormatter.getInstance();
			handler.setFormatter(format);
			LOG.addHandler(handler);
		} catch (IOException ioe) {
			LOG.warning("FileHandler cannot be instanciated... Please contact the dev team"); //$NON-NLS-1$
		} catch (SecurityException se) {
			LOG.warning("FileHandler cannot be instanciated... Please contact the dev team"); //$NON-NLS-1$
		}
	}

	/**
	 * Initialisation des propriétés définies dans le fichier <code>resources/config.properties</code>
	 * @param configFilePath Fichier de configuration à utiliser
	 */
	private static void initializeProperties(String configFilePath) {
		try {
			Properties config = System.getProperties();
			config.load(new FileInputStream(configFilePath));
			for (String prop : config.stringPropertyNames()) {
				if (prop.startsWith("evinrude")) {
					LOG.config(prop + " = " + config.getProperty(prop));
				}
			}
			System.setProperties(config);
		} catch (IOException e) {
			LOG.severe("Config file not loaded [" + e.getMessage() + "]");
		}
	}
}

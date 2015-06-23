package fr.lip6.move.evinrude.compiler;

import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IExecutable;
import fr.lip6.move.evinrude.commons.utils.log.EvinrudeLogFormatter;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Classe se chargeant de la compilation des IDS d'une IApplication.
 *
 * @author Clément Démoulins
 * @author Jean-Baptiste Voron
 * * Class being responsible for the compilation of an IDS IApplication.
  *dropoff window
  * @ Author Clement Démoulins
  * @ Author Jean-Baptiste Voron
 */
public class Compiler {
	/** Le logger */
	private static final Logger LOG = Logger.getLogger(Compiler.class.getName());

	private String compileFilePath;

	/**
	 * Classe lisant un flux et écrivant dans un logger
	 * @author Clément Démoulins
	 * @author Jean-Baptiste Voron
	 * Class reading a stream and writing to a log
* @ Author Clement Démoulins
* @ Author Jean-Baptiste Voron
	 */
	public static class StreamToLogRunnable implements Runnable {
		private Logger logger;
		private Level level;
		private BufferedReader reader;

		/**
		 * @param logger logger
		 * @param level niveau de sortie des logs
		 * @param input flux à lire
		 * *param Logger logger
 *param Level output level logs
 *param Input stream to read
		 */
		public StreamToLogRunnable(Logger logger, Level level, InputStream input) {
			this.logger = logger;
			this.level = level;
			this.reader = new BufferedReader(new InputStreamReader(input));
		}

		/** {@inheritDoc}
		 */
		@Override
		public final void run() {
			String line;
			try {
				while ((line = reader.readLine()) != null) {
					logger.log(level, line);
				}
			} catch (IOException e) {
				logger.warning(e.getMessage());
			}
		}
	}

	/**
	 * Constructor
	 */
	public Compiler() {
		this.compileFilePath = System.getProperty("user.dir") + "/resources/compile.sh";
	}

	/**
	 * Lancement de la compilation, la méthode est synchrone.
	 * @param executable Compilation de cet executables
	 * @return valeur de retour de la compilation
	 * @throws IOException Impossible de rendre le script de compilation
	 * @throws InterruptedException Intérruption lors de l'exécution d'une commande
	 */
	/**dropoff window
	* Launch of the compilation, the method is synchronous.
	*param Executable binaries of this Compilation
	*return Return value compilation
	*throws IOException Can not make the build script
	*throws InterruptedException interruption during the execution of a command
	*/
	public final int compile(IExecutable executable) throws IOException, InterruptedException {
		EvinrudeLogFormatter.getInstance().setIndent(0);
		LOG.log(Level.INFO, "Compilation for " + executable.getName());
		EvinrudeLogFormatter.getInstance().increaseIndent();

		LOG.info("compile:step1");
		LOG.log(Level.INFO, "compilefiepath:" + compileFilePath);
		
		// chmod +x compile.sh
		/*ProcessBuilder chmod = new ProcessBuilder("chmod", "+x", "compile.sh");
		Process chmodProcess = chmod.start();
		LOG.fine("chmod return " + chmodProcess.waitFor());
		LOG.info("compile:step2");
		// make bianca
		LOG.log(Level.INFO, "biancafiepath:" + executable.getBiancaFolder().getAbsolutePath());
		ProcessBuilder compile = new ProcessBuilder("compile.sh", executable.getBiancaFolder().getAbsolutePath());
		LOG.info("compile:tosrtingb" +compile.toString());
		final Process compileProcess = compile.start();
		EvinrudeLogFormatter.getInstance().increaseIndent();
		LOG.info("compile:step3");
		// stdout
		new Thread(new StreamToLogRunnable(LOG, Level.FINE, compileProcess.getInputStream())).start();

		// stderr
		new Thread(new StreamToLogRunnable(LOG, Level.WARNING, compileProcess.getErrorStream())).start();

		// On attend que la compilation soit finie
		//// It is expected that the compilation is finished
		int exitValue = compileProcess.waitFor();
		*/
		//sav:to be removed
		int exitValue = 1;
		//sav
		
		//EvinrudeLogFormatter.getInstance().decreaseIndent();
		LOG.info("compile:step4");
		LOG.fine("compile.sh return " + exitValue);
		EvinrudeLogFormatter.getInstance().decreaseIndent();
		LOG.info("End of compilation of " + executable.getName());

		return exitValue;
	}
}

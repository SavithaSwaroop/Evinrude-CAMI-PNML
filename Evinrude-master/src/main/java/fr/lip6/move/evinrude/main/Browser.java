package fr.lip6.move.evinrude.main;

import fr.lip6.move.evinrude.commons.model.cfg.interfaces.IExecutable;
import fr.lip6.move.evinrude.parser.FtpFile;
import fr.lip6.move.evinrude.parser.IFile;
import fr.lip6.move.evinrude.parser.LocalFile;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.logging.Logger;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;

/**
 * Classe chargée du parcours d'un répertoire afin d'en faire sortir tous les fichiers à analyser
 * @author Jean-Baptiste Voron
 */
/**dropoff window
* Class responsible for a directory path in order to bring out all the files to be scanned
* @ Author Jean-Baptiste Voron
*/
public final class Browser {
	/** Le logger */
	private static Logger LOG = Logger.getLogger(Browser.class.getName());

	/** Constructeur */
	private Browser() {
	}

	/**
	 * Construit une liste de fichiers contenant des informations de CFG
	 * @param directory Le répertoire qui doit être parcouru
	 * @return La liste des fichiers
	 */
	/**dropoff window
	* Made a list of files containing information CFG
	*param Directory The directory to be scanned
	*return The file list
	*/
	public static List<IFile> buildFileList(String directory) {
		List<IFile> toReturn = new ArrayList<IFile>();
		File dir = new File(directory);

		// Parcours recursif
	
	
		int i=0;
		for (File item : dir.listFiles()) {
			i++;
			LOG.info("dir.listfiles0:"+item.getPath());
			LOG.info("value of dir:"+i);
			// Si c'est un repertoire
			if (item.isDirectory()) {
				LOG.info("step1");
				toReturn.addAll(buildFileList(item.getPath()));
			}
			LOG.info("step2");
			// Si c'est un fichier
			//// If it's a file
			if (item.isFile() && item.getName().endsWith(".cfg")) {
				LOG.info("step3");
				LOG.fine("|" + item.getPath());
				toReturn.add(new LocalFile(item));
				LOG.info("step4");
			}
			LOG.info("step5");

		
		}
		 LOG.info("step6");
		return toReturn;
	}

	/**
	 * @return un FTPClient connecté et logué au serveur de benchs.
	 * @throws IOException en cas de problème de communication avec le serveur.
	 */
	/**dropoff window
	 *return A connected and logged in to the server benchs FtpClient.
	 *throws IOException if a problem communicating with the server.
	 */
	private static FTPClient openBenchConnection() throws IOException {
		// Parametres de configuration
		String user = System.getProperty("evinrude.benchs.user", "anonymous");
		String password = System.getProperty("evinrude.benchs.password", "");
		String host = System.getProperty("evinrude.benchs.host");
		int port = Integer.valueOf(System.getProperty("evinrude.benchs.port", "21"));

		LOG.fine("  Connection au serveur ftp : " + user + ":" + password + "@" + host + ":" + port);
		LOG.info("openbenchconnecton");
		// Initialisation de la connection au serveur de benchs
		FTPClient ftp = new FTPClient();
		ftp.connect(host, port);
		LOG.info("openbenchconnecton1");
		if (!FTPReply.isPositiveCompletion(ftp.getReplyCode())) {
			ftp.disconnect();
			throw new IOException(ftp.getReplyString());
		}
		if (!ftp.login(user, password)) {
			throw new IOException(ftp.getReplyString());
		}

		ftp.enterLocalPassiveMode();
		LOG.fine("  Connection réussi");

		return ftp;
	}

	/**
	 * @param ftp connection FTP à fermer
	 */
	private static void closeConnection(FTPClient ftp) {
		if (ftp.isConnected()) {
			try {
				ftp.logout();
				ftp.disconnect();
			} catch (IOException e) {
				LOG.warning("Erreur à la fermeture de la connexion [" + e.getMessage() + "]");
			}
		}
	}

	/**
	 * @return Liste des applications disponible sur le serveur de benchs.
	 */
	//*return List of applications available on the benchs server.
	public static List<String> listBenchApplications() {
		try {
			LOG.info("listbenchapplications");
			String path = System.getProperty("evinrude.benchs.path");
			FTPClient ftp = openBenchConnection();
			LOG.info("listbenchapplications1");
			List<String> apps = new ArrayList<String>();
			for (FTPFile file : ftp.listFiles(path)) {
				if (file.isDirectory()) {
					LOG.finer("    Application disponible : " + file.getName());
					apps.add(file.getName());
				}
			}

			ftp.disconnect();
			return apps;

		} catch (IOException e) {
			LOG.warning("Impossible d'accéder au dépôt de benchs [" + e.getMessage() + "]");
			return new ArrayList<String>(0);
		}
	}

	/**
	 * @param applicationName application pour laquel on veut récupérer les CFG.
	 * @return un iterateur sur les fichiers CFG de l'application.
	 */
	public static Iterator<IFile> findBenchCfg(String applicationName) {
		try {
			String path = System.getProperty("evinrude.benchs.path");

			// Création de l'itérateur sur les fichiers CFG disponibles.
			final FTPClient ftp = openBenchConnection();
			final Iterator<String> cfgsIterator = findFile(ftp, path + "/" + applicationName, ".*\\.cfg").iterator();

			return new Iterator<IFile>() {
				public boolean hasNext() {
					boolean hasNext = cfgsIterator.hasNext();
					if (!hasNext) {
						LOG.finer("Close FTP connection.");
						closeConnection(ftp);
					}
					return hasNext;
				}

				public FtpFile next() {
					String filename = cfgsIterator.next();
					LOG.finer("Ouverture du CFG : " + filename);

					return new FtpFile(ftp, filename);
				}

				public void remove() {
				}
			};

		} catch (NumberFormatException e) {
			LOG.warning("Problème de configuration du port pour accéder au dépôt de benchs [" + e.getMessage() + "]");
		} catch (IOException e) {
			LOG.warning("Impossible d'accéder au dépôt de benchs [" + e.getMessage() + "]");
		}
		// En cas d'erreur on retourne un iterateur vide
		return new ArrayList<IFile>(0).iterator();
	}

	/**
	 * @param executable executable concerné
	 * @return une liste de trace pour l'executable
	 */
	public static Iterator<IFile> findIDSTrace(IExecutable executable) {
		try {
		String path = System.getProperty("evinrude.benchs.path")
								+ "/" + executable.getApplication().getName();
			final FTPClient ftp = openBenchConnection();
			final Iterator<String> traces = findFile(ftp, path, executable.getName() + "\\.\\d+\\.\\d+\\.trace").iterator();

			return new Iterator<IFile>() {
				public boolean hasNext() {
					boolean hasNext = traces.hasNext();
					if (!hasNext) {
						LOG.finer("Close FTP connection.");
						closeConnection(ftp);
					}
					return hasNext;
				}

				public FtpFile next() {
					String filename = traces.next();
					LOG.finer("Ouverture du fichier de trace : " + filename);

					return new FtpFile(ftp, filename);
				}

				public void remove() {
				}
			};
		} catch (NumberFormatException e) {
			LOG.warning("Problème de configuration du port pour accéder au dépôt de benchs [" + e.getMessage() + "]");
		} catch (IOException e) {
			LOG.warning("Impossible d'accéder au dépôt de benchs [" + e.getMessage() + "]");
		}
		// En cas d'erreur on retourne un iterateur vide
		return new ArrayList<IFile>(0).iterator();
	}

	/**
	 * @param ftp instance d'un FTPClient connecté et logué
	 * @param path chemin où rechercher les fichiers CFG
	 * @param regex les fichiers doivent 'matcher' cette regex
	 * @return liste de chemin absolu de tous les fichier CFG contenu dans le dossier path ainsi que dans tous les
	 * sous-dossiers.
	 */
	private static List<String> findFile(FTPClient ftp, String path, String regex) {
		List<String> files = new ArrayList<String>();

		try {
			FTPFile[] ftpFiles = ftp.listFiles(path);
			for (FTPFile file : ftpFiles) {
				if (file.isDirectory()) {
					files.addAll(findFile(ftp, path + "/" + file.getName(), regex));
				} else if (file.isFile() && file.getName().matches(regex)) {
					files.add(path + "/" + file.getName());
				}
			}
		} catch (IOException e) {
			LOG.warning("Erreur lors de la recherche de CFG dans le dossier '" + path + "'");
		}

		return files;
	}
}

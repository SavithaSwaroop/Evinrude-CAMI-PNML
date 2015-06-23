package fr.lip6.move.evinrude.commons.model.petri;

/**
 * Définition d'une variable colorée pour un réseau de Petri.<br>
 * Une variable est toujours attachée à une classe de couleur.
 *
 * @author Jean-Baptiste Voron
 */
public class ColoredVariable {
	/** Le nom de la variable */
	private String name;

	/** La classe de couleur associée */
	private String colorClass;

	/**
	 * Constructeur
	 * @param name Le nom de la variable
	 * @param colorClass La classe de couleur associée à la variable
	 */
	public ColoredVariable(String name, String colorClass) {
		this.name = name;
		this.colorClass = colorClass;
	}

	/**
	 * @return la classe de couleur associée
	 */
	public final String getColorClass() {
		return colorClass;
	}

	/**
	 * @return le nom de la variable
	 */
	public final String getName() {
		return name;
	}
}

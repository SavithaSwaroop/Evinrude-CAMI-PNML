package fr.lip6.move.evinrude.commons.model.petri.interfaces;

import java.util.List;

/**
 * Description des comportements publics d'une classe de couleurs
 * @author Jean-Baptiste Voron
 */
public interface IColorClass {
	/** Type : Intervalle de valeurs */
	int RANGE = 0;
	/** Type : Ensemble de valeurs */
	int ENUM = 1;

	/**
	 * @return le nom de la classe de couleur
	 */
	String getName();

	/**
	 * Ajoute un intervalle de valeurs dans la classe de couleurs
	 * @param min La borne min
	 * @param max La borne max
	 * @return Le nombre d'éléments ajoutés
	 */
	int addRange(int min, int max);

	/**
	 * Ajoute des valeurs dans la classe de couleurs
	 * @param values Les valeurs à ajouter
	 * @return le nombre de valeurs effectivement ajoutées
	 */
	int addValues(String... values);

	/**
	 * Ajoute des valeurs dans la classe de couleurs
	 * @param values Les valeurs à ajouter
	 * @return le nombre de valeurs effectivement ajoutées
	 */
	int addValues(List<String> values);

	/**
	 * Supprime des valeurs de la classe de couleur
	 * @param values Les valeurs à supprimer de la classe
	 * @return le nombre de valeurs effectivement supprimées
	 */
	int removeValues(String... values);

	/**
	 * @return les valeurs de la class de couleur
	 */
	List<String> getValues();

	/**
	 * @return le type de la classe de couleur
	 * @see IColorClass
	 */
	int getType();
}

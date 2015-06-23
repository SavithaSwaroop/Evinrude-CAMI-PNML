package fr.lip6.move.evinrude.builder;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Règle permettant de transformer un élément du modéle CFG en un morceau de réseau de petri.<br>
 * Le système de dépendance permet aux règles filles de passer après leurs parents et de récupérer et modifier leurs
 * modèles.<br>
 * <br>
 * Exemple : A —> B<br>
 * Le modèle que retourne B est passé à A qui peut le modifier puis retourne un modèle qui est enfin inclus au réseau de
 * petri général.
 * TODO : mettre à jour
 */
/**
 * Rule for transforming an element of CFG model into a petri network piece . <br>
 * The dependency system allows girls to pass rules after their parents and to retrieve and modify their
 * Models. <br>
 * <br>
 * Example: A -> B <br>
 * The model B is passed back to A , which can change the then returns a model that is finally included in the network
 * General Petri .
 * TODO : update
 * @author sneeth
 *
 */
public interface IRule {
	List<String> EMPTY_DEPENDENCIES = Collections.unmodifiableList(new ArrayList<String>(0));
	List<IProperty> EMPTY_PROPERTIES = Collections.unmodifiableList(new ArrayList<IProperty>(0));

	/**
	 * @return Le nom de la règle.
	 */
	String getName();

	/**Dependency list ( rules of names ) for this rule.
	 * @return Liste de dépendance (des noms de régles) pour cette régle.
	 */
	List<String> getDependencies();

	/**
	 * @return list of properties, only local properties can be attach to a rule.
	 */
	List<IProperty> getProperties();

}

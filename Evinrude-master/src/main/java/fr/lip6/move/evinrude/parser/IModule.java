package fr.lip6.move.evinrude.parser;


/**dropoff window
  * Interface defining a parser module.
  */
  // id generator
  
public interface IModule {
	/**dropoff window
	* Checks if the module can perform processing on a line.
	*param Line line check
	*return <Code> true </ code> if the line can be treated <code> false </ code> if
	*/ //id
	boolean match(String line);

	/**
	 * Traitement de la ligne sur le ICfg
	 * @param line ligne à traiter
	 * @return <code>true</code> si la ligne a été parsé <code>false</code> sinon
	 */
	/**dropoff window
	* Treatment of the line on the ICFG
	*param Line line to be processed
	*return <Code> true </ code> if the line has been parsed <code> false </ code> if
	*/
	//dropoff window
	boolean process(String line);
}

package fr.lip6.move.evinrude.commons.utils;

import fr.lip6.move.pnml.framework.utils.IdRepository;
import fr.lip6.move.pnml.ptnet.hlapi.TransitionHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.NameHLAPI;
import fr.lip6.move.pnml.framework.utils.IdRepository;
import fr.lip6.move.pnml.framework.utils.ModelRepository;
import fr.lip6.move.pnml.framework.utils.PNMLUtils;
import fr.lip6.move.pnml.framework.utils.exception.InvalidIDException;
import fr.lip6.move.pnml.framework.utils.exception.VoidRepositoryException;
import fr.lip6.move.pnml.framework.general.PnmlExport;
import fr.lip6.move.pnml.framework.hlapi.HLAPIRootClass;
import fr.lip6.move.pnml.ptnet.hlapi.ArcHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.NodeHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.PageHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.PetriNetDocHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.PetriNetHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.PNTypeHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.PlaceHLAPI;
import fr.lip6.move.pnml.ptnet.hlapi.RefPlaceHLAPI;
import org.eclipse.emf.ecore.EFactory;
/*import fr.lip6.move.pnml.framework.utils.exception.ImportException;
import fr.lip6.move.pnml.framework.utils.exception.InvalidIDException;
import fr.lip6.move.pnml.framework.utils.logging.LogMaster;
import org.slf4j.Logger;
*/
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IArc;
//import fr.lip6.move.evinrude.commons.model.petri.interfaces.IGuard;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IModel;
//import fr.lip6.move.evinrude.commons.model.petri.interfaces.INode;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.IPlace;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ISubModel;
import fr.lip6.move.evinrude.commons.model.petri.interfaces.ITransition;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.concurrent.ConcurrentMap;
import java.util.logging.Logger;

/**
 * Classe utilitaire pour l'export en DOT d'un modèle.<br>
 * La hiérarchie du modèle est retranscrite sous forme de clusters DOT.
 *
 * @author Jean-Baptiste Voron
 */
/**
 * Utility class for export in DOT of a model. <br>
 * The hierarchy of the model is transcribed as DOT clusters.
 *
 * @ Author Jean-Baptiste Voron
 * @author sneeth
 *
 */
public final class PNMLExport {
	/** Le logger */
	//private static Logger LOG = LogMaster.getLogger(PNMLExport.class.getName());
	private static Logger LOG = Logger.getLogger(PNMLExport.class.getName());
	/** Constructeur */
	private PNMLExport() { }
	
	static String idValue;


	private static String toPNML(ISubModel model) {

		return "hello";
	}


		
	public static void dumpPNMLRepresentation(IModel model, String id, File outputDirectory) throws InvalidIDException, VoidRepositoryException {
		System.out.print("inside dumponml");
		PetriNetDocHLAPI doc = new PetriNetDocHLAPI();
		System.out.print("ousdie doc");
		IdRepository R=new IdRepository();
		idValue =R.generateFreeId(id,model);
		
		LOG.info("idValveid is "+idValue);

		
		PetriNetHLAPI net=new PetriNetHLAPI(idValue,PNTypeHLAPI.COREMODEL,doc);
		PageHLAPI page = new PageHLAPI("toppage", new NameHLAPI("myname"),null, net); //use of "null" is authorized but not encouraged 
		PageHLAPI subpage = new PageHLAPI("subpage", new NameHLAPI("toto"),null, page);
		
		PlaceHLAPI[] Places= new PlaceHLAPI[5];
		int i=0;
		for (IPlace place : model.getPlaces()) {
			//PlaceHLAPI Places[i++]= new PlaceHLAPI(place.getName());
			}	

		
		PlaceHLAPI p1 = new PlaceHLAPI("place1");
		PlaceHLAPI p2 = new PlaceHLAPI("place2");
		PlaceHLAPI p3 = new PlaceHLAPI("place3");

		TransitionHLAPI t1 = new TransitionHLAPI("transistion1");
		TransitionHLAPI t2 = new TransitionHLAPI("transistion2");

		RefPlaceHLAPI r1 = new RefPlaceHLAPI("reftop3", p3);

		new ArcHLAPI("a1", p1, t1, page);
		new ArcHLAPI("a2", t1, r1, page);
		new ArcHLAPI("a3", p3, t2, subpage);
		new ArcHLAPI("a4", t2, p2, subpage);

		p1.setContainerPageHLAPI(page);
		t1.setContainerPageHLAPI(page);
		r1.setContainerPageHLAPI(page);

		p3.setContainerPageHLAPI(subpage);
		p2.setContainerPageHLAPI(subpage);
		t2.setContainerPageHLAPI(subpage);

	
			for (ITransition transition : model.getTransitions()){
				
				TransitionHLAPI  Transitions= new TransitionHLAPI(transition.getName());
			}
		for (IArc arc : model.getArcs())
			{		
			new ArcHLAPI("id",(NodeHLAPI)arc.getSource(), (NodeHLAPI)arc.getTarget());//a1 has to change to arc name
			}	
			try {
				  PnmlExport pex = new PnmlExport();
				  pex.exportObject(doc, outputDirectory.getAbsolutePath() + "/exporttest.pnml");
				}
			catch(Exception e)
				{System.out.println(e);} 
			
		try {
			String filename = model.getHead().getName() + "_" + id + ".pnml";
			PrintWriter pnmlExport = new PrintWriter(new BufferedWriter(new FileWriter(outputDirectory.getAbsolutePath() + "/" + filename)));
			pnmlExport.print(PNMLExport.toPNML(model));
			pnmlExport.close();
			LOG.config("\t   The PNML representation :: " + id + " :: is available in: " + filename);
		} catch (IOException e) {
			System.err.println("Erreur lors de la construction du graphe dot " + e.getMessage());
			e.printStackTrace();
		}
		/*
			String filename = model.getHead().getName() + "_" + id + ".pnml";
			String s=PNMLExport.toPNML(model);
			File file=new File(filename);
		//	PrintWriter pnmlExport = new PrintWriter(new BufferedWriter(new FileWriter(f)));
						try{  
				FileWriter fileWritter = new FileWriter(file.getName(),true);
		        BufferedWriter bufferWritter = new BufferedWriter(fileWritter);
		        bufferWritter.write(s);
		        bufferWritter.close();
				  }
			catch(Exception e)
			{System.out.println(e);}  
		/*	try {
				HLAPIRootClass h=PNMLUtils.importPnmlDocument(file,false);
				PnmlExport pex = new PnmlExport();
				pex.exportObject(h, outputDirectory.getAbsolutePath() + "/exporttest.pnml");
				} 
			catch(Exception e)
				{System.out.println(e);} 
		//	pnmlExport.close();
		//	LOG.config("\t   The PNML representation :: " + id + " :: is available in: " + filename);
*/
		}
}




package org.citygraph.light.core.model.owl;

import java.util.ArrayList;
import java.util.List;

public class OntologiesSet {

	protected static OntologiesSet primary;
	private List<Ontology> ontologies;
	
	protected OntologiesSet() {
		
		ontologies = new ArrayList<Ontology>();
		
	}
	
	public static OntologiesSet get() {
		
		if(primary == null) {
			
			primary = new OntologiesSet();
		}
		
		return primary;
		
	}
	
	public static void updateMainOntology(Ontology ontology) {
		
		
		setMainOntology(ontology);
		
	}
	
	public static void addThirdPartyOntology(Ontology ontology) {
		
		
		setThirdPartyOntology(ontology);
		
	}
	
	public static Ontology getMainOntology() {
		
		return new Ontology();
		
	}
	
	private static void setThirdPartyOntology(Ontology ontology) {
		// TODO Auto-generated method stub
		
		
	}

	private static void setMainOntology(Ontology ontology) {
		
		ontology.setAsMain();
		
		checkOntologyInList(ontology);
		
	}

	private static void checkOntologyInList(Ontology ontology) {
		// TODO Auto-generated method stub
		
	}
	
	

}

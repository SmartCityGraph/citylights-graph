package org.citygraph.light.core.model;

import java.util.List;

import org.citygraph.light.core.model.owl.OntologiesSet;

public class Table {
	
	private String name;
	private List<Field> fields;
	private String id;
	private String label;
	
	public String getLabel() {
		return label;
	}

	public void setLabel(String label) {
		this.label = label;
	}

	public Table (String name) {
	
		name = OntologiesSet.get().getMainOntology().getPrefix()+"_"+name;
	}
	
	public Table (String name, String prefix) {
		
		name = prefix +"_"+name;
		
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<Field> getFields() {
		return fields;
	}

	public void setFields(List<Field> fields) {
		this.fields = fields;
	}
	
	
	public void addField(Field field) {
		fields.add(field);
	}
	
	public void addPrimaryKey() {
		
	}
	
	public void addForeighnKey() {
		
	}

}

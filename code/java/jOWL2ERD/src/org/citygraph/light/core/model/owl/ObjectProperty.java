package org.citygraph.light.core.model.owl;

public class ObjectProperty implements Property {
	
	private String name;
	private Individual subject;
	private Individual object;
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public Individual getSubject() {
		return subject;
	}
	public void setSubject(Individual subject) {
		this.subject = subject;
	}
	public Individual getObject() {
		return object;
	}
	public void setObject(Individual object) {
		this.object = object;
	}

}

package org.citygraph.light.core.model.owl;

public class DataProperty implements Property {

	private String name;
	private Individual subject;
	private Object object;
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
	public Object getObject() {
		return object;
	}
	public void setObject(Object object) {
		this.object = object;
	}
}

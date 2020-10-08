package org.citygraph.light.core.model.owl;

import java.util.List;

public class Ontology {
	
	protected boolean main;
	protected boolean thirdParty;
	private String uri;
	private String prefix;
	private List<Individual> individuals;
	
	public String getUri() {
		return uri;
	}
	public void setUri(String uri) {
		this.uri = uri;
	}
	public String getPrefix() {
		return prefix;
	}
	public void setPrefix(String prefix) {
		this.prefix = prefix;
	}
	public boolean isMain() {
		return main;
	}
	protected void setAsMain() {
		this.main = true;
		this.thirdParty = false;
	}
	public boolean isThirdParty() {
		return thirdParty;
	}
	protected void setAsThirdParty() {
		this.thirdParty = true;
		this.main = false;
	}
	
	

}

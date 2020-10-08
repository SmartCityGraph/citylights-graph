package org.citygraph.light.core.model;

public class Settings {

	// нужно ли на основе индивидов заполнять базу данных
	public static boolean generate_examples = true;

	// используется для имени поля в таблице для финального класса (который по сути
	// является категорией, по умолчанию category)
	public static String final_class_cat_name = "category";

	// true - приоритет онтологии, false - приоритет у индивидов
	public static boolean ont_prefered = false;

}

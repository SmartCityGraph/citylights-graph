#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;

ofstream relation_database;
ofstream service_map;

map <string, string> classes;
map <string, string> tables;


vector <string> tables_done;

int line_count = 1;


class table
{
public:
    string name_in_ontology;
    string name_table;
    boolean category;
    vector <string> atributs;
};

int char_pos(string line, char char_needed, int order)
{
    if (order == 0) {
        return -1;
    }
    int char_counter = 0;
    int quotes_count = 0;
    int brackets_count = 0;
    int i = 0;
    while (line[i] != '\0')
    {
        if (((quotes_count % 2) == 0) && ((brackets_count % 2) == 0))
        {
            if (line[i] == char_needed)
            {
                char_counter++;
            }
            if (char_counter == order)
            {
                return i;
            }
        }
        if (line[i] == '\"')
        {
            quotes_count++;
        }
        if ((line[i] == '(') || (line[i] == ')'))
        {
            brackets_count++;
        }
        i++;
    }
    return line.length();
}

string atribut(int atr_num, string line)
{
    int first_char = char_pos(line, ',', atr_num - 1) + 1;
    int second_char = char_pos(line, ',', atr_num);
    line = line.substr(first_char, (second_char - first_char));
    if (line.length() == 0)
    {
        return "";
    }
    else
    {
        return line;
    }
}

int main()
{
    ifstream ontology("ontology.ttl");
    map <string, string> classes_name;
    map <string, string> type;
    type["xsd:int"] = "INT";
    type["xsd:boolean"] = "BOOL";


    service_map.open("service.txt");
    string line;
    int liness;

    int objamount = 0;
    int datamount = 0;
    int clasamount = 0;

    string object_property_list[100][10];
    string data_property_list[100][7];
    string classes_list[100][10];
    string classes_list_safe[100][8];
    string table_list;

    int classes_link_list[100][2];
    int classes_link_list_safe[100];
    int object_property_link_list[100][2];
    int data_property_link_list[100];
    
    getline(ontology, line);
    int lines = line.find("#    Object Properties");
    while (lines < 0)
    {
        getline(ontology, line);
        lines = line.find("#    Object Properties");
    }
    lines = line.find("#    Individuals");
    while (lines < 0)
    {
        getline(ontology, line);

        liness = line.find("###  ");
        lines = line.find("#    Individuals");
        if (liness > -1)
        {
            string line = "!";
            string atribut;
            string atributs[10];
            int atribut_begin;
            int atribut_end;
            int lines;
            atributs[3] = "yes";
            atributs[4] = "";
            while (line != "")
            {
                getline(ontology, line);
                lines = line.find("rdf:type");
                if (lines > -1)
                {
                    

                    atribut_begin = 0;
                    atribut_end = char_pos(line, ' ', 1);
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    
                    atributs[1] = atribut;
                    classes_name[atribut] = atribut;
                    atribut_begin = char_pos(line, ' ', 2)+1;
                    atribut_end = char_pos(line, ' ', 3);
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    atributs[0] = atribut;
                    
                    cout << classes_name[atribut] << " name" << endl;

                }
                
                
       
                lines = line.find("subClassOf");
                if (lines > -1)
                {
                    atribut_begin = line.find("subClassOf") + 11;
                    atribut_end = line.length() - 2;
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    atributs[2] = atribut;
                    atributs[3] = "";
                }
                    lines = line.find("ERDname");
                    if (lines > -1)
                    {
                        atribut_begin = line.find("ERDname") + 9;
                        atribut_end = line.length() - 3;
                        atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                        atributs[4] = atribut;
                        classes_name[atributs[1]] = atribut;

                    }
                    lines = line.find("reverseProperty");
                    if (lines > -1)
                    {
                        atributs[9] = "yes";
                    }
                    
                
                lines = line.find("notConvertable");
                if (lines > -1)
                {
                    atributs[3] = "";
                }
                lines = line.find("domain");
                if (lines > -1)
                {
                    atribut_begin = line.find("domain") + 7;
                    atribut_end = line.length() - 2;
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    atributs[5] = atribut;
                }
                lines = line.find("range");
                if (lines > -1)
                {
                    atribut_begin = line.find("range") + 6;
                    atribut_end = line.length() - 2;
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    atributs[6] = atribut;
                }
                lines = line.find("areDomains");
                if (lines > -1)
                {
                    atribut_begin = line.find("areDomains") + 12;
                    atribut_end = line.length() - 3;
                    atribut = line.substr(atribut_begin, atribut_end - atribut_begin);
                    
                    if (atributs[0] == "owl:ObjectProperty")
                    {
                        object_property_list[objamount][0] = atributs[1];
                        object_property_list[objamount][1] = atribut;
                        object_property_list[objamount][2] = atributs[6];
                        object_property_list[objamount][3] = atributs[4];
                        object_property_list[objamount][4] = "0";
                        object_property_list[objamount][5] = "";
                        object_property_list[objamount][6] = "";
                        object_property_list[objamount][9] = atributs[9];
                        object_property_link_list[objamount][0] = -1;
                        object_property_link_list[objamount][1] = 0;

                        objamount++;
                    }
                    if (atributs[0] == "owl:DatatypeProperty")
                    {
                        data_property_list[datamount][0] = atributs[1];
                        data_property_list[datamount][1] = atribut;
                        data_property_list[datamount][2] = atributs[6];
                        data_property_list[datamount][3] = atributs[4];
                        data_property_list[datamount][4] = "0";
                        data_property_list[datamount][5] = "";
                        data_property_link_list[datamount] = -1;
                        datamount++;
                    }
                }
            }

            if (atributs[0] == "owl:ObjectProperty")
            {
                object_property_list[objamount][0] = atributs[1];
                object_property_list[objamount][1] = atributs[5];
                object_property_list[objamount][2] = atributs[6];
                object_property_list[objamount][3] = atributs[4];
                object_property_list[objamount][4] = "0";
                object_property_list[objamount][5] = "";
                object_property_list[objamount][6] = "";
                object_property_list[objamount][9] = atributs[9];
                object_property_link_list[objamount][0] = -1;
                object_property_link_list[objamount][1] = 0;

                objamount++;
            }
            if (atributs[0] == "owl:DatatypeProperty")
            {
                data_property_list[datamount][0] = atributs[1];
                data_property_list[datamount][1] = atributs[5];
                data_property_list[datamount][2] = atributs[6];
                data_property_list[datamount][3] = atributs[4];
                data_property_list[datamount][4] = "0";
                data_property_list[datamount][5] = "";
                data_property_link_list[datamount] = -1;
                datamount++;
            }
            if (atributs[0] == "owl:Class")
            {
                classes_list[clasamount][0] = atributs[1];
                classes_list[clasamount][1] = atributs[2];
                classes_list[clasamount][2] = atributs[3];
                classes_list[clasamount][3] = atributs[4];
                classes_list[clasamount][4] = atributs[5];
                classes_list[clasamount][5] = "";
                classes_list[clasamount][6] = "";
                classes_list[clasamount][9] = "";
                
                classes_list_safe[clasamount][0] = atributs[1];
                classes_list_safe[clasamount][1] = atributs[2];
                classes_list_safe[clasamount][2] = atributs[3];
                classes_list_safe[clasamount][3] = atributs[4];
                classes_list_safe[clasamount][4] = atributs[5];
                classes_list_safe[clasamount][5] = "";
                classes_list_safe[clasamount][6] = "";
                classes_link_list[clasamount][0] = clasamount;
                classes_link_list[clasamount][1] = 0;
                classes_link_list_safe[clasamount] = clasamount;

                if (classes_list[clasamount][2] == "yes")
                {
                    classes_list[clasamount][4] = "1";
                    classes_list_safe[clasamount][4] = "1";
                    //classes_list[clasamount][5] = clasamount;
                    //classes_list_safe[clasamount][5] = clasamount;
                    classes_link_list[clasamount][0] = clasamount;
                    classes_link_list_safe[clasamount] = clasamount;
                }
                if (classes_list[clasamount][3] == "yes")
                {
                    classes_list[clasamount][4] = "1";
                    classes_list_safe[clasamount][4] = "1";
                }
                clasamount++;
            }
            service_map << atributs[0] << "," << atributs[1] << "," << atributs[2] << "," << atributs[3] << "," << atributs[4] << "," << atributs[5] << "," << atributs[6] << endl;
        }
    }
        /*service_map.close();
        ifstream service("service.txt");
        ofstream service_two;
        service_two.open("service_two.txt");
        int objamount = 0;
        int datamount = 0;
        int clasamount = 0;
        getline(service, line);
        string object_property_list[100][6];
        string data_property_list[100][6];
        string classes_list[100][7];
        string classes_list_safe[100][7];
        string table_list;

        while (line != "")
        {
            cout << atribut(1, line) << endl;
            if (atribut(1, line) == "owl:ObjectProperty")
            {
                object_property_list[objamount][0] = atribut(2, line);
                object_property_list[objamount][1] = atribut(6, line);
                object_property_list[objamount][2] = atribut(7, line);
                object_property_list[objamount][3] = atribut(5, line);
                object_property_list[objamount][4] = "0";
                object_property_list[objamount][5] = "";
                
                objamount++;
            }
            if (atribut(1, line) == "owl:DatatypeProperty")
            {
                data_property_list[datamount][0] = atribut(2, line);
                data_property_list[datamount][1] = atribut(6, line);
                data_property_list[datamount][2] = atribut(7, line);
                data_property_list[datamount][3] = atribut(5, line);
                data_property_list[datamount][4] = "0";
                data_property_list[datamount][5] = "";
                datamount++;
            }
            if (atribut(1, line) == "owl:Class")
            {
                classes_list[clasamount][0] = atribut(2, line);
                classes_list[clasamount][1] = atribut(3, line);
                classes_list[clasamount][2] = atribut(4, line);
                classes_list[clasamount][3] = atribut(5, line);
                classes_list[clasamount][4] = atribut(6, line);
                classes_list[clasamount][5] = "";
                classes_list[clasamount][6] = "";
                classes_list_safe[clasamount][0] = atribut(2, line);
                classes_list_safe[clasamount][1] = atribut(3, line);
                classes_list_safe[clasamount][2] = atribut(4, line);
                classes_list_safe[clasamount][3] = atribut(5, line);
                classes_list_safe[clasamount][4] = atribut(6, line);
                classes_list_safe[clasamount][5] = "";
                classes_list_safe[clasamount][6] = "";

                if (classes_list[clasamount][2] == "yes")
                {
                    classes_list[clasamount][4] = "1";
                    classes_list_safe[clasamount][4] = "1";
                    classes_list[clasamount][5] = clasamount;
                    classes_list_safe[clasamount][5] = clasamount;
                }
                if (classes_list[clasamount][3] == "yes")
                {
                    classes_list[clasamount][4] = "1";
                    classes_list_safe[clasamount][4] = "1";
                }
                clasamount++;
            }
            getline(service, line);
        }*/

        int obj_check = 1;
        int data_check = 1;
        int class_check = 1;
        int fix;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if ((classes_list[i][0] == data_property_list[j][1]) && (classes_list[i][0] != "") && (data_property_list[j][1] != ""))
                {
                    cout << classes_list[i][0] << " " << data_property_list[j][1] << endl;

                    if (classes_list[i][2] == "yes")
                    {
                        data_property_list[j][3] = "yes";
                        data_property_link_list[j] = i;
                    }
                    else
                    {
                        classes_list[i][6] = classes_list[i][6] + data_property_list[j][0] + "," + data_property_list[j][2] + ",";
                        classes_link_list[i][1]++;
                    }
                }
            }
        }
        cout << "data check done";
           while (class_check > 0)
           {
               
               class_check = 0;
               for (int i = 0; i < 100; i++)
               {
                   if ((classes_list[i][2] == "") && (classes_list[i][1] != "") && (classes_list[i][4] == ""))
                   {
                       for (int j = 0; j < 100; j++)
                       {
                           if (classes_list[i][1] == classes_list_safe[j][0])
                           {
                               classes_list[j][9] = "yes";
                               if (classes_list_safe[j][2] == "yes")
                               {
                                   classes_list[i][4] = "1";
                                   fix = j;
                                   classes_list[i][5] = fix;
                                   classes_link_list[i][0] = j;
                               }
                               else if (classes_list_safe[j][1] != "")
                               {
                                   classes_list[i][1] = classes_list_safe[j][1];
                               }
                               else if ((classes_list_safe[j][1]== "") && (classes_list_safe[j][2] == ""))
                               {
                                   classes_list[i][4] = "1";
                               }
                               if (classes_list[i][4] != "1")
                               {
                                   class_check++;
                               }
                           }
                       }
                   }
                   if ((classes_list[i][1] == ""))
                   {
                       classes_list[i][4] == "1";
                   }
               }
           }
           cout << "class check done";
           while (obj_check > 0)
           {
               obj_check = 0;
               for (int i = 0; i < 100; i++)
               {
                   if (object_property_list[i][0] != "")
                   {
                       int domain_num;
                       int range_num;
                       for (int j = 0; j < 100; j++)
                       {
                           if ((classes_list[j][0] == object_property_list[i][1]) && (classes_list[j][0] != "") && (object_property_list[i][1] != ""))
                           {
                               
                               domain_num = j;
                               cout << domain_num;
                           }
                           if ((classes_list[j][0] == object_property_list[i][2]) && (classes_list[j][0] != "") && (object_property_list[i][2] != ""))
                           {
                               
                               range_num = j;
                               cout << range_num;
                           }
                       }
                       if ((classes_list[domain_num][2] == "yes") && (classes_list[range_num][2] == "yes"))
                       {
                           object_property_list[i][4] = "1";
                           object_property_list[i][5] = range_num;
                           object_property_link_list[i][0] = range_num;
                           object_property_list[i][6] = "yes";
                           if (object_property_list[i][9] == "yes")
                           {
                               object_property_list[i][5] = domain_num;
                               object_property_link_list[i][0] = domain_num;
                           }

                       }
                       else if ((classes_list[domain_num][2] == "yes") && (classes_list[range_num][2] == ""))
                       {
                           cout << object_property_list[i][0] << " " << object_property_list[i][1] << " " << object_property_list[i][2] << " " << domain_num << " " << range_num << endl;
                           object_property_list[i][4] = "2";
                           classes_list[range_num][5] = domain_num;
                           object_property_list[i][6] = classes_list[range_num][6];
                           cout << endl << endl << endl << object_property_list[i][5] << endl << classes_list[range_num][6] << endl << endl << endl;
                           object_property_link_list[i][1] = classes_link_list[range_num][1];
                           classes_link_list[range_num][0] = domain_num;
                           object_property_list[i][5] = domain_num;
                           object_property_link_list[i][0] = domain_num;
                           cout << classes_link_list[range_num][0] << endl;
                       }
                       else if ((classes_list[domain_num][2] == "") && (classes_list[range_num][2] == ""))
                       {
                           object_property_list[i][1] = classes_list[classes_link_list[domain_num][0]][0];

                       }
                       if (object_property_list[i][4] == "0")
                       {
                           obj_check++;

                       }
                   }
               }
           }
           cout << "obj check done";
        

                 ofstream service_map_three;
                 service_map_three.open("service_three");
                 for (int i = 0; i < 100; i++)
                 {
                     if (object_property_list[i][0] != "")
                     {
                         service_map_three << object_property_list[i][0] << ',' << object_property_list[i][1] << ',' << object_property_list[i][2] << ',' << object_property_list[i][3] << ',' << object_property_list[i][4] << ',' << object_property_list[i][5] << ',' << object_property_list[i][6] << ',' << object_property_link_list[i] << endl;
                     }
                 }
                 for (int i = 0; i < 100; i++)
                 {
                     if (classes_list[i][0] != "")
                     {
                         service_map_three << classes_list[i][0] << ',' << classes_name[classes_list[i][0]] << "," << classes_list[i][1] << ',' << classes_list[i][2] << ',' << classes_list[i][3] << ',' << classes_list[i][4] << ',' << classes_link_list[i] << ',' << classes_list[i][6] << endl;
                     }
                 }
                 for (int i = 0; i < 100; i++)
                 {
                     if (data_property_list[i][0] != "")
                     {
                         service_map_three << data_property_list[i][0] << ',' << data_property_list[i][1] << ',' << data_property_list[i][2] << ',' << data_property_list[i][3] << ',' << data_property_list[i][4] << ',' << data_property_link_list[i] << endl;
                     }
                 }

                 for (int i = 0; i < 100; i++)
                 {
                     if (classes_list[i][2] == "yes")
                     {
                         if (classes_list[i][3] == "")
                         {
                             string ontology_prefix = "";
                             int has;
                             int is;
                             string atribut_name = classes_list[i][0];
                             
                             if (char_pos(atribut_name, ':', 1) != 0)
                             {
                                 ontology_prefix = atribut_name.substr(0, char_pos(atribut_name, ':', 1)) + "_";
                                 cout << ontology_prefix << endl;
                             }
                             int tap_begin = char_pos(atribut_name, ':', 1)+1;
                             int tap_length = (atribut_name.length() - (tap_begin));
                             string atribut_change = atribut_name.substr(tap_begin, tap_length);
                             cout << atribut_change << endl;

                             has = atribut_change.find("has");
                             is = atribut_change.find("is");
                             if (has == 0)
                             {
                                 atribut_change = atribut_change.substr(3, atribut_change.length() - 3);
                             }
                             if (is == 0)
                             {
                                 atribut_change = atribut_change.substr(2, atribut_change.length() - 2);
                             }
                             atribut_change = "CL_" + ontology_prefix + atribut_change;
                             cout << atribut_change << endl;
                             service_map_three << "CREATE TABLE " << atribut_change << " (" << endl;
                         }
                         else
                         {
                             service_map_three << "CREATE TABLE " << classes_list[i][3] << " (" << endl;
                         }
                         service_map_three << "id INT" << endl;
                         service_map_three << "label STRING" << endl;
                         if (classes_list[i][9] == "yes")
                         {
                             service_map_three <<"category STRING" << endl;
                         }
                         for (int j = 0; j < 100; j++)
                         {
                             if (data_property_list[j][0] != "")
                             {
                                 cout << data_property_list[j][0] << " " << data_property_link_list[j] << endl;
                                 if (data_property_link_list[j] == i && data_property_list[j][3] == "yes")
                                 {
                                     string ontology_prefix = "";
                                     int has;
                                     int is;
                                     string atribut_name = data_property_list[j][0];

                                     if (char_pos(atribut_name, ':', 1) != 0)
                                     {
                                         ontology_prefix = atribut_name.substr(0, char_pos(atribut_name, ':', 1)) + "_";
                                         cout << ontology_prefix << endl;
                                     }
                                     int tap_begin = char_pos(atribut_name, ':', 1) + 1;
                                     int tap_length = (atribut_name.length() - (tap_begin));
                                     string atribut_change = atribut_name.substr(tap_begin, tap_length);
                                     cout << atribut_change << endl;

                                     has = atribut_change.find("has");
                                     is = atribut_change.find("is");
                                     if (has == 0)
                                     {
                                         atribut_change = atribut_change.substr(3, atribut_change.length() - 3);
                                     }
                                     if (is == 0)
                                     {
                                         atribut_change = atribut_change.substr(2, atribut_change.length() - 2);
                                     }
                                     atribut_change = "CL_" + ontology_prefix + atribut_change;
                                     cout << atribut_change << endl;
                                     service_map_three << atribut_change;
                                     if (type[data_property_list[j][2]] == "")
                                     {
                                         service_map_three << " STRING" << endl;
                                     } 
                                     else
                                     {
                                         service_map_three << " " << type[data_property_list[j][2]] << endl;
                                     }
                                     }
                             }
                             if (object_property_list[j][0] != "")
                             {
                                 cout << object_property_list[j][0] << " " << object_property_link_list[j][0] << endl;
                                 if (object_property_link_list[j][0] == i)
                                 {
                                     if (object_property_list[j][6] == "yes")
                                     {
                                         string atribut_change;
                                         string ontology_prefix = "";
                                         int has;
                                         int is;
                                         string atribut_name = classes_name[object_property_list[j][1]];
                                         if (object_property_list[j][9] == "yes")
                                         {
                                             atribut_name = classes_name[object_property_list[j][2]];
                                         }
                                         int l = atribut_name.find(":", 0);
                                         
                                             if (l != -1)
                                             { 
                                                 cout << atribut_name << endl;

                                                 if (char_pos(atribut_name, ':', 1) != 0)
                                                 {
                                                     ontology_prefix = atribut_name.substr(0, char_pos(atribut_name, ':', 1)) + "_";
                                                         cout << ontology_prefix << endl;
                                                 }
                                             int tap_begin = char_pos(atribut_name, ':', 1) + 1;
                                                 int tap_length = (atribut_name.length() - (tap_begin));
                                                 atribut_change = atribut_name.substr(tap_begin, tap_length);
                                                 cout << atribut_change << endl;

                                             has = atribut_change.find("has");
                                             is = atribut_change.find("is");
                                             if (has == 0)
                                             {
                                                 atribut_change = atribut_change.substr(3, atribut_change.length() - 3);
                                             }
                                             if (is == 0)
                                             {
                                                 atribut_change = atribut_change.substr(2, atribut_change.length() - 2);
                                             }
                                         }
                                         else
                                         {
                                             atribut_change = atribut_name;
                                         }
                                         atribut_change = "CL_" + ontology_prefix + atribut_change + "_id";
                                         cout << atribut_change << endl;
                                         service_map_three << atribut_change << endl;
                                     }
                                     else
                                     {
                                         for (int m = 1; m <= object_property_link_list[j][1]*2; m++)
                                         {
                                             string ontology_prefix = "";
                                             int has;
                                             int is;
                                             string atribut_name = object_property_list[j][0];
                                             /* if (classes_list[i][3] != "")
                                              {
                                                  atribut_name = ":" + classes_list[j][3] + "_id";
                                              }*/
                                             cout << atribut_name << " " << j << endl;

                                             if (char_pos(atribut_name, ':', 1) != 0)
                                             {
                                                 ontology_prefix = atribut_name.substr(0, char_pos(atribut_name, ':', 1)) + "_";
                                                 cout << ontology_prefix << endl;
                                             }
                                             int tap_begin = char_pos(atribut_name, ':', 1) + 1;
                                             int tap_length = (atribut_name.length() - (tap_begin));
                                             string atribut_change = atribut_name.substr(tap_begin, tap_length);
                                             cout << atribut_change << endl;

                                             has = atribut_change.find("has");
                                             is = atribut_change.find("is");
                                             if (has == 0)
                                             {
                                                 atribut_change = atribut_change.substr(3, atribut_change.length() - 3);
                                             }
                                             if (is == 0)
                                             {
                                                 atribut_change = atribut_change.substr(2, atribut_change.length() - 2);
                                             }
                                             atribut_change = "CL_" + ontology_prefix + atribut_change;
                                             service_map_three << atribut_change;

                                             ontology_prefix = "";
                                             
                                             atribut_name = atribut(m,object_property_list[j][6]);
                                             /* if (classes_list[i][3] != "")
                                              {
                                                  atribut_name = ":" + classes_list[j][3] + "_id";
                                              }*/
                                             cout << atribut_name << endl;

                                             if (char_pos(atribut_name, ':', 1) != 0)
                                             {
                                                 ontology_prefix = atribut_name.substr(0, char_pos(atribut_name, ':', 1)) + "_";
                                                 cout << ontology_prefix << endl;
                                             }
                                             tap_begin = char_pos(atribut_name, ':', 1) + 1;
                                             tap_length = (atribut_name.length() - (tap_begin));
                                             atribut_change = atribut_name.substr(tap_begin, tap_length);
                                             cout << atribut_change << endl;

                                             has = atribut_change.find("has");
                                             is = atribut_change.find("is");
                                             if (has == 0)
                                             {
                                                 atribut_change = atribut_change.substr(3, atribut_change.length() - 3);
                                             }
                                             if (is == 0)
                                             {
                                                 atribut_change = atribut_change.substr(2, atribut_change.length() - 2);
                                             }
                                             atribut_change = "_" + ontology_prefix + atribut_change;
                                             service_map_three << atribut_change;
                                             if (type[atribut(2 * m, object_property_list[j][6])] != "")
                                             {
                                                 service_map_three << " " << type[atribut(2 * m, object_property_list[j][6])] << endl;
                                             }
                                             else
                                             {
                                                 service_map_three << " STRING" << endl;
                                             }
                                             m++;
                                         }
                                     }
                                 }
                             }
                         }
                         service_map_three << ");" << endl;
                     }
                 }
            /* }*/
             ontology.close();

}


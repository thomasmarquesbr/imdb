//
//  Menu.cpp
//  imdb
//
//  Created by Thomás Marques on 01/05/17.
//  Copyright © 2017 Thomás Marques. All rights reserved.
//

#include <iostream>
#include "Menu.hpp"

using namespace std;

void Menu::showHeader(){
    cout << "********************************************* IN MEMORY DATABASE - Parte 2 *********************************************** " << endl;
    cout << "**     Curso: Mestrado em Ciência da Computação - UFJF                                                                  ** " << endl;
    cout << "**     Disciplina: Algoritmos e estruturas de dados                                                                     ** " << endl;
    cout << "**     Professor: Jairo Francisco de Souza                                                                              ** " << endl;
    cout << "**     Aluno: Thomás Marques Brandão Reis                                                                               ** " << endl;
    cout << "************************************************************************************************************************** " << endl;
    cout << endl;
}

void Menu::showMainMenu(Database *database){
    int choice = 0;
    while (choice != -1) {
        cout << "       / Menu Principal" << endl;
        cout << endl;
        cout << "       1. Banco de dados" << endl;
        cout << "       2. Tabelas" << endl;
        cout << "       3. Sair" << endl;
        cout << endl;
        cout << "       >> ";
        cin >> choice;
        cin.clear(); cin.ignore(INT_MAX,'\n');
        switch (choice) {
            case 1:
                showMenuDatabase(database);
                break;
            case 2:
                showMenuTables(database);
                break;
            case 3:
                choice = -1;
                cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
                break;
            default:
                cout << endl;
                cout << "       Escolha inválida." <<endl;
                cout << endl;
                cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
                break;
        }
    }
}

void Menu::showMenuDatabase(Database *database){
    int choice = 0;
    while(choice != -1) {
        cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
        cout << "       / Menu Principal / Banco de Dados" << endl;
        cout << endl;
        cout << "       1. Listar informações do banco" <<endl;
        cout << "       2. Leitura de arquivo para popular o banco" <<endl;
        cout << "       3. Realizar consulta SQL (apenas com chavees primárias)" <<endl;
        cout << "       4. Realizar consulta SQL (com chave estrangeira e primária, respectivamente)" <<endl;
        cout << "       5. Voltar" <<endl;
        cout << endl;
        cout << "       >> ";
        cin >> choice;
        cin.clear(); cin.ignore(INT_MAX,'\n');
        switch (choice) {
            case 1:{
                cout << endl;
                cout << "       Total de tabelas: " + to_string(database->getAmountTables()) <<endl;
                if (database->getFirstTable() != NULL)
                    cout << "       Primeira tabela: " + database->getFirstTable()->getName() <<endl;
                if (database->getLastTable() != NULL)
                    cout << "       Última tabela: " + database->getLastTable()->getName() <<endl;
                if (database->getCreationTime() != 0.0)
                    cout << "       Tempo de criação da estrutura: " << database->getCreationTime() << " segundos." << endl;
                cout << endl;
                break;
            }
            case 2:{
                cout << endl;
                cout << "       Digite o caminho do arquivo. Ex: \"/Users/Username/Documents/file.txt\" (X para sair)" << endl;
                cout << "       >> ";
                string path;
                cin >> path;
                cin.clear(); cin.ignore(BC_STRING_MAX,'\n');
                if (path.at(0) != 'X' && !path.empty()) {
                    database->readFile(path);
                }
                cout << endl;
                break;
            }
            case 3:{
                cout << endl;
                cout << "       Digite a consulta sql. (X para sair)" << endl;
                cout << "       >> ";
                string querySql;
                string ok;
                getline(cin, querySql);
                cin.ignore();
                if (querySql.at(0) != 'X' && !querySql.empty()) {
                    database->executeParserSql(querySql, true);
                }
                cout << endl;
                break;
            }
            case 4:{
                cout << endl;
                cout << "       Digite a consulta sql. (X para sair)" << endl;
                cout << "       >> ";
                string querySql;
                string ok;
                getline(cin, querySql);
                cin.ignore();
                if (querySql.at(0) != 'X' && !querySql.empty()) {
                    database->executeParserSql(querySql, false);
                }
                cout << endl;
                break;
            }
            case 5:{
                choice = -1;
                cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
                break;
            }
            default:{
                cout << endl;
                cout << "       Escolha inválida." <<endl;
                cout << endl;
                break;
            }
        }
    }
}

void Menu::showMenuTables(Database *database){
    int choice = 0;
    while(choice != -1) {
        cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
        cout << "       / Menu Principal / Tabelas" << endl;
        cout << endl;
        cout << "       1. Listar tabelas" <<endl;
        cout << "       2. Criar tabela" <<endl;
        cout << "       3. Buscar tabela" <<endl;
        cout << "       4. Voltar" <<endl;
        cout << endl;
        cout << "       >> ";
        cin >> choice;
        cin.clear(); cin.ignore(INT_MAX,'\n');
        switch (choice) {
            case 1:{
                database->printTables();
                cout << endl;
                break;
            }
            case 2:{
                cout << endl;
                cout << "       Digite o nome da tabela. (X para sair)" << endl;
                cout << "       >> ";
                string name;
                name = "";
                cin >> name;
                cin.clear(); cin.ignore(INT_MAX,'\n');
                if (name.at(0) != 'X') {
                    Table *table = new Table(name);
                    cout << endl;
                    cout << "       Digite o atributo da tabela. (X para sair)" << endl;
                    cout << "       >> ";
                    string attribute;
                    while (cin >> attribute) {
                        cin.clear(); cin.ignore(BC_STRING_MAX,'\n');
                        if (attribute.at(0) != 'X') {
                            cout << endl;
                            cout << "       É chave primária? (S ou N)" << endl;
                            cout << "       >> ";
                            char isPrimaryKey;
                            cin >> isPrimaryKey;
                            cin.clear(); cin.ignore(CHAR_MAX,'\n');
                            if (isPrimaryKey == 'S')
                                table->addAttribute(attribute, true);
                            else
                                table->addAttribute(attribute);
                            cout << endl;
                            cout << "       Digite o atributo da tabela. (X para sair)" << endl;
                            cout << "       >> ";
                        } else {
                            break;
                        }
                    }
                    if (table->existPrimaryKey())
                        database->addTable(table);
                    else {
                        cout << endl << "       A tabela deve conter pelo menos 1 atributo chave, portanto ela não foi criada. " << endl;
                        delete table;
                    }
                    cin.clear();
                } else
                    cout << endl << "       A tabela não foi criada. " << endl;
                break;
            }
            case 3:{
                cout << endl;
                cout << "       Digite o nome da tabela. (X para sair)" << endl;
                cout << "       >> ";
                string name;
                name = "";
                cin >> name;
                cin.clear(); cin.ignore(INT_MAX,'\n');
                double time = 0.0;
                if (name.at(0) != 'X') {
                    database->startTime();
                    Table *table = database->getTable(name);
                    database->endTime(&time);
                    if (table != NULL){
                        cout << endl << "       Tempo de busca: " << time << " segundos." << endl;
                        cout << endl;
                        showMenuSearchTable(table);
                    } else {
                        cout << endl << "       A tabela \"" + name +  "\" não existe." << endl;
                        cout << "       Tempo de busca: " << time << " segundos." << endl;
                        cout << endl;
                    }
                }
                break;
            }
            case 4:{
                choice = -1;
                cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
                break;
            }
            default:{
                cout << endl;
                cout << "       Escolha inválida." <<endl;
                cout << endl;
                break;
            }
        }
    }
}

void Menu::showMenuSearchTable(Table *table){
    int choice = 0;
    while(choice != -1) {
        cout << "  ---------------------------------------------------------------------------------------------------------------------- " << endl;
        cout << "       / Menu Principal / Tabelas / "+table->getName() << endl;
        cout << endl;
        cout << "       1. Listar informações da tabela " << endl;
        cout << "       2. Inserir registro " << endl;
        cout << "       3. Remover registro " << endl;
        cout << "       4. Buscar registro" << endl;
        cout << "       5. Exibir registros PreOrdem" << endl;
        cout << "       6. Exibir registros InOrdem" << endl;
        cout << "       7. Exibir registros PosOrdem" << endl;
        cout << "       8. Exibir árvore de registros" << endl;
        cout << "       9. Voltar" << endl;
        cout << endl;
        cout << "       >> ";
        cin >> choice;
        cin.clear(); cin.ignore(INT_MAX,'\n');
        switch (choice) {
            case 1:{
                cout << endl;
                cout << "       Total de registros: " + to_string(table->getAmountElements()) <<endl;
                table->printAttributes();
                if (table->getRootElement() != NULL)
                    cout << "       Registro raiz: " + table->getRootElement()->getKey() <<endl;
                cout << endl;
                break;
            }
            case 2:{
                Attribute *attribute = table->getFirstAttribute();
                Element *element = new Element();
                string valueAttrib;
                while (attribute != NULL) {
                    cout << endl;
                    cout << "       Digite o nome do valor para o atributo \"" + attribute->getName() +"\" (I para ignorar, X para sair)" << endl;
                    cout << "       >> ";
                    cin >> valueAttrib;
                    cin.clear(); cin.ignore(BC_STRING_MAX,'\n');
                    if (valueAttrib.at(0) == 'X')
                        break;
                    else if (valueAttrib.at(0) == 'I')
                        attribute = attribute->getNext();
                    else {
                        element->addField(attribute->getName(), valueAttrib);
                        attribute = attribute->getNext();
                    }
                }
                double time = 0.0;
                if (element->getFirstField() != NULL){
                    table->startTime();
                    table->addElement(element);
                    table->endTime(&time);
                    cout << "       Tempo de inserção: " << time << " segundos." << endl;
                } else {
                    cout << endl << "       O registro deve conter pelo menos a chave primária. O registro não foi criado" << endl;
                }
                cout << endl;
                break;
            }
            case 3:{
                cout << endl;
                cout << "       Digite a chave do registro. (X para sair)" << endl;
                cout << "       >> ";
                string key;
                key = "";
                cin >> key;
                cin.clear(); cin.ignore(BC_STRING_MAX,'\n');
                double time = 0.0;
                cout << endl;
                table->startTime();
                if (table->removeElement(key))
                    cout << "       Registro removido com sucesso." << endl;
                else
                    cout << "       Registro não existe na tabela." << endl;
                table->endTime(&time);
                cout << endl;
                cout << "       Tempo de remoção: " << time << " segundos." << endl;
                break;
            }
            case 4:{
                cout << endl;
                cout << "       Digite a chave do registro. (X para sair)" << endl;
                cout << "       >> ";
                string key;
                key = "";
                cin >> key;
                cin.clear(); cin.ignore(BC_STRING_MAX,'\n');
                double time = 0.0;
                table->startTime();
                Element *element = table->findElement(key);
                table->endTime(&time);
                cout << endl;
                if (element != NULL) {
                    element->printFields();
                } else
                    cout << "       Registro não existe na tabela." << endl;
                cout << "       Tempo de busca: " << time << " segundos." << endl;
                break;
            }
            case 5:{
                table->printElementsPreOrdem();
                break;
            }
            case 6:{
                table->printElementsInOrdem();
                break;
            }
            case 7:{
                table->printElementsPosOrdem();
                break;
            }
            case 8:{
                table->drawTree();
                break;
            }
            case 9:{
                choice = -1;
                break;
            }
            default:{
                cout << endl;
                cout << "       Escolha inválida." <<endl;
                cout << endl;
                break;
            }
        }
    }
}

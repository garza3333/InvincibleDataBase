//
// Created by kugelblitz on 5/25/19.
//

#ifndef INVINCIBLE_SERVER_REQUESTHANDLER_H
#define INVINCIBLE_SERVER_REQUESTHANDLER_H

#include <pistache/endpoint.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace Pistache;
using nlohmann::json;
using boost::property_tree::ptree;

class requestHandler: public Http::Handler {
private:
    DataBase * dataBase = new DataBase();
    JManager * jMan = new JManager();

public:

HTTP_PROTOTYPE(requestHandler);

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {





        dataBase->addGalery("Photos");
        dataBase->addGalery("vacaciones");

        //IMAGEN 1
        ptree pt;
        pt.put("table","Photos");
        pt.put("cols","name,author,description,year,size");
        pt.put("values","danielImage,GARZA,its a test image,2019,3");


        //IMAGEN2
        ptree pt2;
        pt2.put("table","Photos");
        pt2.put("cols","name,description,size,author,year");
        pt2.put("values","danielImage,this shit,2000,SOFIA,2018");


        //IMAGEN3
        ptree pt3;
        pt3.put("table","Photos");
        pt3.put("cols","name,description,size,author,year");
        pt3.put("values","gabriel,this is a description,2000,GARZA,2019");


        //IMAGEN4
        ptree pt4;
        pt4.put("table","Photos");
        pt4.put("cols","name,description,size,author,year");
        pt4.put("values","danielImage,i need coffee,1023,SOFIA,2019");

        dataBase->insertImage(jMan->ptreeToString(pt));
        dataBase->insertImage(jMan->ptreeToString(pt2));
        dataBase->insertImage(jMan->ptreeToString(pt3));
        dataBase->insertImage(jMan->ptreeToString(pt4));


        std::string datos;
        std::string respuesta  = "false";
        if (request.method() == Http::Method::Post) {

            if (request.resource() == "/CREATE") {
                std::cout << "Se recibe create request con cuerpo : " << datos << std::endl;
                datos = request.body();

                dataBase->addGalery(datos);
                cout<<"galery added "<<datos<<endl;

                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            else if (request.resource() == "/RESTORE") {

                datos= request.body();

                respuesta = dataBase->initIdleTree();


                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            if (request.resource() == "/INSERT") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);
                std::cout << "Se recibe json : " << jsonRequest.dump(4) << std::endl;

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                //std::string jsonString = jsonRequest.dump();

                // TODO aqui debe estar logica del insert



                if(this->dataBase->insertImage(jsonRequest.dump())){
                    ptree pt;
                    pt.put("id",dataBase->getImageId()-1);
                    respuesta = this->jMan->ptreeToString(pt);
                }


                cout<<respuesta<<endl;

                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            else if (request.resource() == "/SELECT") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */



                // TODO aqui debe estar logica del select

                respuesta = this->jMan->ptreeToString(dataBase->selectImage(jsonRequest.dump()));


                cout<<respuesta<<endl;

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, respuesta);
            }

            else if (request.resource() == "/UPDATE") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                // TODO aqui debe estar logica del update

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, jsonRequest.dump(4));
            }

            else if (request.resource() == "/DELETE") {
                datos = request.body();

                auto jsonRequest = json::parse(datos);

                /*
                 * Para accesar a parametros del json seria:
                 * var valor = jsonRequest[nomDeLaLlave]
                 */

                // TODO aqui debe estar logica del delete

                // TODO definir respuesta
                response.send(Pistache::Http::Code::Ok, jsonRequest.dump(4));
            }

        }
        else {
            std::cout << "se envio respuesta defeault" << std::endl;
            response.send(Pistache::Http::Code::Ok, "<h1>Esta es la respuesta por defecto</h1>");
        }
    }

};

#endif //INVINCIBLE_SERVER_REQUESTHANDLER_H
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
        std::string datos;
        std::string respuesta  = "false";
        if (request.method() == Http::Method::Post) {
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

                dataBase->addGalery("vacaciones");
                try {

                    if(this->dataBase->insertImage(jsonRequest.dump())){
                        ptree pt;
                        pt.put("id",dataBase->getImageId()-1);
                        respuesta = this->jMan->ptreeToString(pt);
                    }
                }catch(...){
                    cout<<"Exception in server INSERT"<<endl;
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
                try{

                    respuesta = this->jMan->ptreeToString(dataBase->selectImage(jsonRequest.dump()));
                }catch(...){
                    cout<<"Exception in server SELECT"<<endl;
                }

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
#include "writer.h"
#include "stringbuffer.h"
#include <iostream>
#include "jsonWriter.h"

namespace jsonGenerator{

using namespace rapidjson;
void createJsonFileBackup(){

    StringBuffer s;
    Writer<StringBuffer> writer(s);
    
    writer.StartObject();
        writer.Key("action");
        writer.String("authorised");
        writer.Key("msg");
        writer.StartObject();
            writer.Key("authorised");
            writer.Bool(true);
            writer.Key("reason");
            writer.String("success");
            writer.Key("designer");
            writer.Bool(true);
            writer.Key("profile");
            writer.StartArray();
                //for (unsigned i = 0; i < 4; i++)
                //    writer.Uint(i);
                writer.StartObject();
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("authLevel");
                    writer.Int(1);
                writer.EndObject();
                writer.StartObject();
                    writer.Key("functionalArea");
                    writer.String("finance");
                    writer.Key("authLevel");
                    writer.Int(1);
                writer.EndObject();
            writer.EndArray();
            writer.Key("forms");
            writer.StartArray();
                writer.StartObject();
                    writer.Key("name");
                    writer.String("orderDetails");
                    writer.Key("type");
                    writer.String("operations");
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("parentArea");
                    writer.String("newOrders");                    
                writer.EndObject();
                writer.StartObject();
                    writer.Key("name");
                    writer.String("orderManagement");
                    writer.Key("type");
                    writer.String("operations");
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("parentArea");
                    writer.String("pendingOrders");                    
                writer.EndObject();
            writer.EndArray();
        writer.EndObject();
    writer.EndObject();







/*    writer.Key("t");
    writer.Bool(true);
    writer.Key("f");
    writer.Bool(false);
    writer.Key("n");
    writer.Null();
    writer.Key("i");
    writer.Uint(123);
    writer.Key("pi");
    writer.Double(3.1416);
    writer.Key("a");
    writer.StartArray();
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);
    writer.EndArray();
*/
    
 
    std::cout << s.GetString() << std::endl;

}



void createJsonFileBackup(){

    StringBuffer s;
    Writer<StringBuffer> writer(s);
    
    Action AuthRequest          --Action confirmed, userConfigData
            SaveData             --Action confirmed
            UpdateData           --Action confirmed
            DeleteData           --Action confirmed
            LoadFormRequest     --From details
            QueryRequest         --QueryMetaData , QueryData
            NewFormRequest       
            UpdateFormRequest
            DeleteForm

    writer.StartObject();
        writer.Key("action");
        writer.String("authorised");
        writer.Key("msg");
        writer.StartObject();
            writer.Key("authorised");
            writer.Bool(true);
            writer.Key("reason");
            writer.String("success");
            writer.Key("designer");
            writer.Bool(true);
            writer.Key("profile");
            writer.StartArray();
                //for (unsigned i = 0; i < 4; i++)
                //    writer.Uint(i);
                writer.StartObject();
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("authLevel");
                    writer.Int(1);
                writer.EndObject();
                writer.StartObject();
                    writer.Key("functionalArea");
                    writer.String("finance");
                    writer.Key("authLevel");
                    writer.Int(1);
                writer.EndObject();
            writer.EndArray();
            writer.Key("forms");
            writer.StartArray();
                writer.StartObject();
                    writer.Key("name");
                    writer.String("orderDetails");
                    writer.Key("type");
                    writer.String("operations");
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("parentArea");
                    writer.String("newOrders");                    
                writer.EndObject();
                writer.StartObject();
                    writer.Key("name");
                    writer.String("orderManagement");
                    writer.Key("type");
                    writer.String("operations");
                    writer.Key("functionalArea");
                    writer.String("sales");
                    writer.Key("parentArea");
                    writer.String("pendingOrders");                    
                writer.EndObject();
            writer.EndArray();
        writer.EndObject();
    writer.EndObject();

    std::cout << s.GetString() << std::endl;

}



};
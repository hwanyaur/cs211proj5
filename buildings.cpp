/*buildings.cpp*/

//
// A footway / path in the Open Street Map.
// 
// Yaurie Hwang
// Northwestern University
// CS 211: Winter 2023
// 

#include "buildings.h"
#include "osm.h"
#include <cassert>

using namespace std;
using namespace tinyxml2;

void Buildings::readMapBuildings(XMLDocument & xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);
    
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr) {
        if (osmContainsKeyValue(way, "building", "university")) {
          string name = osmGetKeyValue(way, "name");
          string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");
          
          const XMLAttribute* attrId = way->FindAttribute("id");
          assert(attrId != nullptr);
          long long id = attrId->Int64Value();

          Building B(id, "NodeIDs", streetAddr);

          XMLElement* nd = way->FirstChildElement("nd");

          while(nd != nullptr) {
            const XMLAttribute* ndref = nd->FindAttribute("ref");
            assert (ndref != nullptr);

            long long id = ndref->Int64Value();
            B.add(id);

            MapBuildings.push_back(B); //adds B to mapbuildings vector
          }// while nd isnt null
    } //if osm contains key value 
    way = way->NextSiblingElement("way"); //gets next way
    }
}



int Buildings::getNumMapBuildings() { 
    int count = 0;
    for (Building B: MapBuildings) {
        count ++;
    }
    return count;
}
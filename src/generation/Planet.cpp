//
// Created by mgkan on 18/07/2022.
//

// Temporary deprecated
//
//#include "generation/Planet.hpp"
//#include "utils/FNV1Hash.hpp"
//
//
//Planet::Planet(std::string name, UniversalPosition position, int size) : CelestialBody(name, position, size), rand(FNV1::Hash( // Generating the SolarSystem seed
//        FNV1::Hash( // Regenerating the parent Seed
//                position.seedUniverse,
//                position.positionGalaxy.x,
//                position.positionGalaxy.y,
//                position.positionGalaxy.z),
//        position.positionSolarSystem.x,
//        position.positionSolarSystem.y,
//        position.positionSolarSystem.z)) {
//    bodyType = Type(rand.Next(0, 9));
//    int rngColor = -1;
//    switch (bodyType) {
//
//        case Chthonian:
//            color = Colour(8);
//            break;
//        case Gas_dwarf:
//            color = Colour(rand.Next(7, 12));
//            break;
//        case Gas_giant:
//            color = Colour(rand.Next(7, 12));
//            break;
//        case Desert:
//            if(rngColor != 9 && rngColor != 10 && rngColor != 14 && rngColor != 13){
//                rngColor = Colour(rand.Next(9, 14));
//            }
//            color = Colour(rngColor);
//            break;
//        case Ocean:
//            if(rngColor != 7 && rngColor != 12 && rngColor != 11 && rngColor != 15){
//                rngColor = Colour(rand.Next(7, 15));
//            }
//            color = Colour(rngColor);
//            break;
//        case Ice:
//            if(rngColor != 7 && rngColor != 15){
//                rngColor = Colour(rand.Next(7, 15));
//            }
//            color = Colour(rngColor);
//            break;
//        case Rocky:
//            if(!(8 <= rngColor && rngColor <= 10) || !(13 <= rngColor && rngColor <= 15)){
//                rngColor = Colour(rand.Next(8, 15));
//            }
//            color = Colour(rngColor);
//            break;
//        case Metal:
//            color = Colour(16);
//            break;
//        case Lava:
//            color = Colour(rand.Next(8, 9));
//            break;
//        case Terran:
//            if(rngColor != 7 && rngColor != 12 && rngColor != 11){
//                rngColor = Colour(rand.Next(7, 12));
//            }
//            color = Colour(rngColor);
//            break;
//    }
//}
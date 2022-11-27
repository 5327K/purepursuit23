// #include "path/waypoint.h"
// #include "path/path.h"
// #include "path/pathbuilder.h"

// #include "purepursuit/purepursuit.h"
// #include "purepursuit/abstractdrivetrain.h"
// #include "purepursuit/simulateddrivetrain.h"

// #include <sstream>
// #include <iostream>

// int main()
// {
//   // TODO: path needs to still be 100% fixed (it still generates a slightly off path)
//   Path generatedPath = PathBuilder(true, 100, 20, 3)
//                            .addPoints({{-90.0, 70.0}, {90.0, 70.0}, {90.0, -70.0}})
//                            .build();

//   std::stringstream ss;
//   ss << generatedPath;
// //   ss << (R"(1 23
// // -90.0 70.0 0.0
// // -74.92488432377073 69.8506153434102 17.36424821912905
// // -59.87453149674212 69.6787947762358 24.54676735963745
// // -44.87717261248712 69.45899114388419 30.042023542479345
// // -29.969029915940848 69.15830229493547 34.6517917796456
// // -15.199717205864708 68.73193763335846 38.681468253603406
// // -0.6395346854866947 68.11598365163417 42.281439111802264
// // 13.609838331268321 67.21849254280717 45.53319970526027
// // 27.400435776033504 65.90537845772485 48.480219935193475
// // 40.51568742827136 63.98036378772197 51.141442852975736
// // 52.63807715669927 61.15582569928499 53.51998894841071
// // 63.301766879107426 57.009755499892776 51.83865290909717
// // 71.82295161268088 50.922607292491676 49.77755327445463
// // 77.62800226867921 41.984763568093875 47.588376064139204
// // 81.58433098843324 31.137924824340292 45.096970115362325
// // 84.28312648867289 19.038577289466275 42.25876343490216
// // 86.12767596742702 6.156038137274771 39.057965101280466
// // 87.39360935032367 -7.157424477620275 35.4690620087714
// // 88.27006913589409 -20.613974313958558 31.438083694026155
// // 88.88802683254407 -33.94709978739801 26.858971355504142
// // 89.33979514759231 -46.8718933106197 21.51163895744986
// // 89.69289584223043 -59.04238425968562 14.806700125593215
// // 90.0 -70.0 0
// // )");

//   // ... robot code starts from here ...

//   // Path works!
//   Path path = Path::read(ss);

//   // for (const Waypoint &pt : path.path)
//   //   std::cout << pt << '\n';

//   const Waypoint currPos = {23, 43};
//   const double heading = -0.8204330463490498;

//   const std::size_t closestPointI = PurePursuit::PurePursuitUtil::getClosestPointIndex(path, currPos);
//   const Waypoint lookaheadPt = PurePursuit::PurePursuitUtil::getLookaheadPoint(path, currPos, 30.0, closestPointI).first;
//   const auto curv = PurePursuit::PurePursuitUtil::calculateCurvatureOfArc(path, currPos, heading, lookaheadPt, 30.0);
//   std::cout << PurePursuit::PurePursuitUtil::calculateLeftWheelTargetVelocity(path.path[closestPointI].targetV, 25.4, curv) << ' ' << PurePursuit::PurePursuitUtil::calculateRightWheelTargetVelocity(path.path[closestPointI].targetV, 25.4, curv) << '\n';

//   return 0;
// }
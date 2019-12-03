#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/segment.hpp>

using Point = boost::geometry::model::point<int, 2, boost::geometry::cs::cartesian>;
using Vec2 = boost::geometry::model::segment<Point>;

std::vector<Vec2> build_vector_path(const std::vector<std::string>& in);
int shortest_path_to_point(const std::vector<Vec2> vec, const Point& p);

int main(const int argc, const char** argv) {
    if (argc < 2) {
        std::cerr << "Missing input file...\n";
        return EXIT_FAILURE;
    }

    std::ifstream in{argv[1]};
    if (!in) {
        std::cerr << "Invalid input file...\n";
        return EXIT_FAILURE;
    }

    std::string wire_one;
    std::string wire_two;
    std::getline(in, wire_one);
    std::getline(in, wire_two);

    std::vector<std::string> wire_one_coords;
    std::vector<std::string> wire_two_coords;
    boost::split(wire_one_coords, wire_one, [](unsigned char c){ return c == ','; });
    boost::split(wire_two_coords, wire_two, [](unsigned char c){ return c == ','; });

    std::vector<Vec2> wire_one_vecs = build_vector_path(wire_one_coords);
    std::vector<Vec2> wire_two_vecs = build_vector_path(wire_two_coords);

    std::vector<Point> intersections;
    for (const auto& vec1 : wire_one_vecs) {
        for (const auto& vec2 : wire_two_vecs) {
            boost::geometry::intersection(vec1, vec2, intersections);
        }
    }

    intersections.erase(begin(intersections));

    int shortest{INT_MAX};
    for (const auto& p : intersections) {
        const int wire_one_distance = shortest_path_to_point(wire_one_vecs, p);
        const int wire_two_distance = shortest_path_to_point(wire_two_vecs, p);
        if (const int distance = wire_one_distance + wire_two_distance; distance < shortest) {
            shortest = distance;
        }
    }

    std::cout << shortest << '\n';

    return EXIT_SUCCESS;
}

std::vector<Vec2> build_vector_path(const std::vector<std::string>& in) {
    std::vector<Vec2> out;
    out.reserve(in.size());
    int curr_x{0};
    int curr_y{0};
    for (const auto& s : in) {
        const int amount = atoi(s.substr(1).c_str());
        switch (s[0]) {
            case 'U': {
                out.push_back({{curr_x, curr_y}, {curr_x, curr_y + amount}});
                curr_y += amount;
                break;
            }
            case 'R': {
                out.push_back({{curr_x, curr_y}, {curr_x + amount, curr_y}});
                curr_x += amount;
                break;
            }
            case 'D': {
                out.push_back({{curr_x, curr_y}, {curr_x, curr_y - amount}});
                curr_y -= amount;
                break;
            }
            case 'L': {
                out.push_back({{curr_x, curr_y}, {curr_x - amount, curr_y}});
                curr_x -= amount;
                break;
            }
        }
    }
    return out;
}

int shortest_path_to_point(const std::vector<Vec2> vec, const Point& p) {
    int curr_len{0};
    const Vec2 pv{p, p};
    for (const auto& v : vec) {
        if (boost::geometry::intersects(pv, v)) {
            curr_len += boost::geometry::length(Vec2{v.first, p});
            break;
        }
        curr_len += boost::geometry::length(v);
    }
    return curr_len;
}

/**
 * LKH.cpp
 * created on : Jan 03 2023
 * author : Z.LEI
 **/

#include "LocalSearch/LKH.hpp"

LKH::LKH() {}
LKH::~LKH() {
    if (std::filesystem::exists(root_dir)) {
        try {
            std::filesystem::remove_all(root_dir);
        } catch (std::exception e) {
            std::cout << "[LKH ERROR] " << e.what() << std::endl;
        }
    }
}

void LKH::setContext(std::string timestamp, int random_value) {
    if (ENV == "LOCAL") {
        lkh_exe = LOCAL_LKH_EXE;
        root_dir = LOCAL_LKH_TMP_ROOT;
    } else if (ENV =="SERVER"){
        lkh_exe = SERVER_LKH_EXE;
        root_dir = SERVER_LKH_TMP_ROOT + "_" + timestamp + "_" + std::to_string(random_value) + "/";
    }
    params_file = root_dir + "params.par";
    problem_file = root_dir + "problem.tsp";
    tour_file = root_dir + "tour.txt";
    result_file = root_dir + "result.txt";
}

List* LKH::run(List* solution, bool adapted){
    auto start = std::chrono::high_resolution_clock::now();
    ListAdapter la;
    if (adapted) {
        solution = la.real2Reduced(solution);
    }

    write(solution);
    std::string str = lkh_exe + " " + params_file;
    const char *cmd = str.c_str();
    system(cmd);
    List* new_solution = read();

    if (adapted) {
        new_solution = la.reduced2Real(new_solution);
    }
    new_solution->evaluate();

    auto end = std::chrono::high_resolution_clock::now();
    if (LOG) std::cout << "LKH solution : " << new_solution->getValue() << " time : " << std::chrono::duration<double> (end - start).count() << " s" << std::endl;
    return new_solution;
}

void LKH::write(List* solution) {
    positions.resize(solution->size(), std::vector<double> {-1, -1});
    Node* p = solution->head();
    for (int i = 0; i < solution->size(); ++i) {
        positions[p->id][0] = p->x;
        positions[p->id][1] = p->y;
        p = p->next;
    }

    try {
        // create dir
        if (! std::filesystem::exists(root_dir)) {
            std::filesystem::create_directory(root_dir);
        }
        // write params
        if (! std::filesystem::exists(params_file)) {
            std::ofstream params_out(params_file);
            if (params_out.is_open()) {
                params_out << "PROBLEM_FILE = " << problem_file << "\n";
                params_out << "TOUR_FILE = " << result_file << "\n";
                params_out << "INITIAL_TOUR_FILE = " << tour_file << "\n";
                params_out << "MOVE_TYPE = 5" << "\n";
                params_out << "RUNS = 1" << "\n";
                params_out << "TRACE_LEVEL = 0" << "\n";
                params_out << "MAX_TRIALS = 10" << "\n";
                params_out.close();
            }
        }

        // write problem
        std::ofstream out(problem_file);
        if (out.is_open()) {
            out << "NAME : lhk" << "\n";
            out << "TYPE : TSP" << "\n";
            out << "DIMENSION : " << solution->size() << "\n";
            out << "EDGE_WEIGHT_TYPE : EUC_2D" << "\n";
            out << "NODE_COORD_SECTION" << "\n";
            for (int i = 0; i < positions.size(); ++i) {
                out << i + 1 << " " << int(positions[i][0] * 1000) << " " << int(positions[i][1] * 1000) << "\n";
            }
            out << "EOF" << "\n";
            out.close();
        }
        else std::cout << "Unable to open file";

        // write tour
        std::ofstream tf_out(tour_file);
        if (tf_out.is_open()) {
            p = solution->head();
            tf_out << "TOUR_SECTION" << "\n";
            for (int i = 0; i < solution->size(); ++i) {
                tf_out << p->id + 1 << "\n";
                p = p->next;
            }
            tf_out << -1 << "\n";
            tf_out << "EOF" << "\n";
            tf_out.close();
        }
        else std::cout << "Unable to open file";
    } catch (std::exception e) {
        std::cout << "[LKH Error] " << e.what() << std::endl;
    }
}

List* LKH::read() {
    std::string data;
    std::ifstream in;
    in.open(result_file);
    // get info of vertices
    List* solution = new List();
    getline(in, data);
    while (data != "TOUR_SECTION") {
        getline(in, data);
    }
    getline(in, data);
    while (data != "-1") {
        std::istringstream iss(data);
        int id;
        iss >> id;
        Node* node = new Node(id-1, positions[id-1][0], positions[id-1][1]);
        solution->add(node);
        getline(in, data);
    }
    in.close();
    return solution;
}

#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <deque>
#include <fstream>
 const int SegmentSize{ 3 * 3 };
 template<typename _Ty>
_Ty AreaVisiblePartWall(char**, const int&, const _Ty&);
int main(void){
    try{
        std::fstream file("input.txt", std::ios_base::in);
        if (!file.is_open()){
            throw (-1);
        }
        else{
            int size{};
            file >> size;
            if ((size < 3) || (size > 33)){
                throw (-2);
            }
            char** data{ new char* [size] };
            for (int i{}; i < size; ++i){
                data[i] = new char[size];
                for (int j{}; j < size; ++j)
                {
                    if (file.eof()){
                        throw (-3);
                    }
                    else{
                        file >> data[i][j];
                    }
                }
            }
            if ((data[0][0] == '#') || (data[size - 1][size - 1] == '#')){
                throw (-4);
            }
            else{
                file.close();
                file.open("output.txt", std::ios_base::out | std::ios_base::trunc);
                file << AreaVisiblePartWall(data, size, SegmentSize) << std::endl;
                return 0;
            }
        }
    }
    catch (int errorid){
        switch (errorid){
        case -1:
            std::cerr << "Error: file 'input.txt' not found" << std::endl;
            break;
        case -2:
            std::cerr << "Error: 'N < 3' or 'N > 50'" << std::endl;
            break;
        case -3:
            std::cerr << "Error: labyrinth not full" << std::endl;
            break;
        case -4:
            std::cerr << "Error: left upper or right lower corner not empty" << std::endl;
            break;
        default:
            std::cerr << "Error: unknown" << std::endl;
        }
        return errorid;
    }
}

template<typename _Ty>
_Ty AreaVisiblePartWall(char** _Labyrinth, const int& _Size, const _Ty& _SegmentSize){
    using Node = std::pair<int, int>;
    std::map<Node, std::set<Node>> Graph{};
    for (int i{}; i < _Size; ++i){
        for (int j{}; j < _Size; ++j){
            if (((i - 1) > -1) && (_Labyrinth[i - 1][j] == '.')){
                Graph[{ i, j }].insert({ i - 1, j });
            }
            if (((i + 1) < _Size) && (_Labyrinth[i + 1][j] == '.')){
                Graph[{ i, j }].insert({ i + 1, j });
            }
            if (((j - 1) > -1) && (_Labyrinth[i][j - 1] == '.')){
                Graph[{ i, j }].insert({ i, j - 1 });
            }
            if (((j + 1) < _Size) && (_Labyrinth[i][j + 1] == '.')){
                Graph[{ i, j }].insert({ i, j + 1 });
            }
        }
    }
    _Ty result{};
     std::deque<Node> Deque{};
    Deque.emplace_back(0, 0);
     std::map<Node, bool> isVisited{};
    while (!Deque.empty()){
        const Node& it = Deque.front();
        if (!isVisited[it]){
            if ((it.first || it.second)){
                if ((it.first - 1) < 0){
                    result += _SegmentSize;
                }
                else if (_Labyrinth[it.first - 1][it.second] == '#'){
                    result += _SegmentSize;
                }
                if ((it.second - 1) < 0){
                    result += _SegmentSize;
                }
                else if (_Labyrinth[it.first][it.second - 1] == '#'){
                    result += _SegmentSize;
                }
            }
            if ((it.first != (_Size - 1)) || (it.second != (_Size - 1))){
                if ((it.first + 1) >= _Size){
                    result += _SegmentSize;
                }
                else if (_Labyrinth[it.first + 1][it.second] == '#'){
                    result += _SegmentSize;
                }
                if ((it.second + 1) >= _Size){
                    result += _SegmentSize;
                }
                else if (_Labyrinth[it.first][it.second + 1] == '#'){
                    result += _SegmentSize;
                }
            }
            isVisited[it] = true;
            Deque.insert(Deque.end(), Graph[it].cbegin(), Graph[it].cend());
        }
        Deque.pop_front();
    }
    return result;
}
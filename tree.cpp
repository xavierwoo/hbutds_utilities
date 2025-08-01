#include "tree.h"

hbutds::EightQueenSolver::EightQueenSolver(){
    for(int& e : Y) e = -1;
    for(bool& e : X) e = false;
    for(bool& e : XaY) e = false;
    for(bool& e : XmY) e = false;
}

void hbutds::EightQueenSolver::place_recursion(int y){
    if(y == 8){ // 已放置完8个皇后，找到一个解
        result.push_back(Y);
        return;
    }

    //在第y行上从左到右依次尝试放置皇后
    for(int x{0}; x<8; ++x){
        //不考虑非法的放置
        if(X[x] == 1 || XaY[x+y] || XmY[x-y+7]) continue;

        Y[y] = x; //记录y行放置的位置
        
        //记录三条占用线
        X[x] = true;
        XaY[x+y] = true;
        XmY[x-y+7] = true;

        //递归放置下一行
        place_recursion(y+1);

        //回溯
        X[x] = false;
        XaY[x+y] = false;
        XmY[x-y+7] = false;
    }
}

void hbutds::EightQueenSolver::solve(){
    place_recursion(0);
}

void hbutds::EightQueenSolver::print() const {
    cout<<format("There are {} solutions!\n", result.size());

    int no{0};
    for(auto& sol : result){
        cout<<format("No.{}:\n", no);
        ++no;

        for(int y{0}; y<8; ++y){
            for(int x{0}; x<8; ++x){
                if(x != sol[y]) cout<<" #";
                else cout<<" Q";
            }
            cout<<"\n";
        }
    }
}

void hbutds::list_files_bfs(const std::filesystem::path& dir_path){
    if (!std::filesystem::exists(dir_path) // 对非法或非文件夹的输入报错
            || !std::filesystem::is_directory(dir_path)){
        std::cerr<<format("Invalid path!\n");
        return;
    }
    queue<std::filesystem::path> que;
    que.push(dir_path);
    while(!que.empty()){
        auto curr {que.front()}; que.pop();
        for(const auto& entry : std::filesystem::directory_iterator(curr)){
            if(std::filesystem::is_directory(entry.path())){//文件夹加入队列
                que.push(entry.path());
            }else{
                cout<<format("{}\n", entry.path().string());//文件名输出到屏幕
            }
        }
    }
}
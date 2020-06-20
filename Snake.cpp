#include "Snake.h"
#include <time.h>
using namespace std;

//for snakeBody class
snakeBody::snakeBody(){
    x=0;
    y=0;
}


snakeBody::snakeBody(int col, int row){ //아 첫번째 꺼를 x로 놔야하는구나;;; x,y좌표로 넣어놨네
    x=col;
    y=row;
}
gatePos::gatePos(){
    g_x = 0;
    g_y = 0;
}

gatePos::gatePos(int g_col,int g_row){
    g_x = g_col;
    g_y = g_row;
}


//for snake class
snake::snake(int level){

    
    setlocale(LC_ALL,"");
    initscr(); 
    start_color();

    // 사용할 색 목록
    init_pair(1,COLOR_RED,COLOR_WHITE);
    init_pair(2,COLOR_WHITE,COLOR_GREEN);

    keypad(stdscr,true);
    nodelay(stdscr,true);
    curs_set(0); 
    noecho();
    resize_term(160,100);
    mvprintw(1,1,"C++ Project");
    border('*','*','*','*','*','*','*','*');
    refresh();

    // play window
    // configurtaion initial size
    max_height = 23;
    max_width = 46;
    play = newwin(max_height,max_width,3,3);

    getmaxyx(play,y,x);
    wborder(play,'x','x','x','x','x','x','x','x');
    wrefresh(play);

    for(int i=0;i<3;i++){
        Rsnake.push_back(snakeBody(24+i,11));  //24 가 x좌표고 ,11이 y좌표 
    }
    // map 할
    if(level == 1){
        mvprintw(1,20,"STAGE 1");

        mission_food =3;
        mission_poison =1;
        mission_gate = 0;

        // score window
    score = newwin(8,20,3,55);
    //  mission window
    mission = newwin(8,20,13,55);
    point  = 0;
    food_cnt = 0;
    poison_cnt = 0;
    gate_cnt = 0;
    mission_food_complete = ' '; // 미션 완료 표시
    mission_poison_complete = ' '; // 미션 완료 표시 --> 조건을 충족하면 food 나 poision 쪽에서 'v'로 바꿔줄겁니다.
    mission_gate_complete = ' ';
    body_length = INIT_LENGTH + food_cnt - poison_cnt;
    speed_interval = 15000;
    current_speed = INIT_SPEED;
    mvwprintw(score,1,4,"Score Board");
    mvwprintw(score,2,3,"B : ");
    mvwprintw(score,3,3,"+ : ");
    mvwprintw(score,4,3,"- : ");
    mvwprintw(score,5,3,"G : ");
    wborder(score,'|','|','-','-','-','-','|','|');
    wrefresh(score);

    mvwprintw(mission,1,5,"Mission");
    mvwprintw(mission,2,3,"B : ()");
    mvwprintw(mission,3,3,"+ : %d (%c)",mission_food,mission_food_complete);
    mvwprintw(mission,4,3,"- : %d (%c)",mission_poison,mission_poison_complete);
    mvwprintw(mission,5,3,"G : %d (%c)",gate_cnt,mission_gate_complete);
    wborder(mission,'|','|','-','-','-','-','|','|');
    wrefresh(mission);
        map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
        for(int i=0;i<y;i++){
            map[i]=new int[x];
        }

        // mapping  mwv (y,x)
        for(int row = 0;row< y;row++){
            for(int col = 0; col < x; col++){
                // Wall
                if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
                    map[row][col]=2;

                }
                // immune Wall
                else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                    map[row][col] = 1;
                }
                // empty space
                else{
                    map[row][col] = 0;

                }
            }
        }
    }

    else if (level ==2 ){
        
        mvprintw(1,20,"STAGE 2");

        mission_food = 5;
        mission_poison = 2;
        mission_gate = 1;
        //23,46
        max_height = 27;
        max_width = 54;
        play = newwin(max_height,max_width,3,3);
        getmaxyx(play,y,x);
        wborder(play,'x','x','x','x','x','x','x','x');

        // score window
    score = newwin(8,20,3,70);
    //  mission window
    mission = newwin(8,20,13,70);
    point  = 0;
    food_cnt = 0;
    poison_cnt = 0;
    gate_cnt = 0;
    mission_food_complete = ' '; // 미션 완료 표시
    mission_poison_complete = ' '; // 미션 완료 표시 --> 조건을 충족하면 food 나 poision 쪽에서 'v'로 바꿔줄겁니다.
    mission_gate_complete = ' ';
    body_length = INIT_LENGTH + food_cnt - poison_cnt;
    speed_interval = 15000;
    current_speed = INIT_SPEED;

    mvwprintw(score,1,4,"Score Board");
    mvwprintw(score,2,3,"B : ");
    mvwprintw(score,3,3,"+ : ");
    mvwprintw(score,4,3,"- : ");
    mvwprintw(score,5,3,"G : ");
    wborder(score,'|','|','-','-','-','-','|','|');
    wrefresh(score);

    mvwprintw(mission,1,5,"Mission");
    mvwprintw(mission,2,3,"B : ()");
    mvwprintw(mission,3,3,"+ : %d (%c)",mission_food,mission_food_complete);
    mvwprintw(mission,4,3,"- : %d (%c)",mission_poison,mission_poison_complete);
    mvwprintw(mission,5,3,"G : %d (%c)",gate_cnt,mission_gate_complete);
    wborder(mission,'|','|','-','-','-','-','|','|');
    wrefresh(mission);

        map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
        for(int i=0;i<y;i++){
            map[i]=new int[x];
        }

        
        for(int i=y/2-5;i<y/2+10;i++){
        mvprintw(i,x/2+1,"|"); //30
        }

       for(int i =x/2-1-5;i<x/2+10;i++){
            mvprintw(y/2-5,i,"_");
        }
        

       for(int i =x/2-1-5;i<x/2+10;i++){
            mvprintw(y/2+9,i,"-");
        }
        

        wrefresh(play);

        // 여기서 설정해도 밑에서 설정해도 map = 2; 가 잘 안먹네요ㅠㅠ  
        for(int i=y/2-10;i<y/2+10;i++){
        map[i][x/2+1] = 2;
        
        }
   
        // mapping  mwv (y,x)

      
        for(int row = 0;row< y;row++){
            for(int col = 0; col < x; col++){
                // Wall
                if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
                    map[row][col]= 2;
                }
                // else if(row == y/2-5 && col ==x/2+1){
                //     for(int j = y/2-5;j<y/2+10;j++){
                //         map[j][col] = 2;
                //     }
                // } 
                
                // else if ((row == x/2 && col == 5) || )
                // immune Wall
                else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                    map[row][col] = 1;
                }
                // empty space
                else{
                    map[row][col] = 0;

                }
            }
        }
    }
    
    else if (level ==3 ){
        mvprintw(1,20,"STAGE 3");

        mission_food =7;
        mission_poison =3;
        mission_gate = 1;
        max_height = 27;
        max_width = 54;
        play = newwin(max_height,max_width,3,3);
        getmaxyx(play,y,x);
        wborder(play,'x','x','x','x','x','x','x','x');

        // score window
    score = newwin(8,20,3,70);
    //  mission window
    mission = newwin(8,20,13,70);
    point  = 0;
    food_cnt = 0;
    poison_cnt = 0;
    gate_cnt = 0;
    mission_food_complete = ' '; // 미션 완료 표시
    mission_poison_complete = ' '; // 미션 완료 표시 --> 조건을 충족하면 food 나 poision 쪽에서 'v'로 바꿔줄겁니다.
    mission_gate_complete = ' ';
    body_length = INIT_LENGTH + food_cnt - poison_cnt;
    speed_interval = 15000;
    current_speed = INIT_SPEED;

    mvwprintw(score,1,4,"Score Board");
    mvwprintw(score,2,3,"B : ");
    mvwprintw(score,3,3,"+ : ");
    mvwprintw(score,4,3,"- : ");
    mvwprintw(score,5,3,"G : ");
    wborder(score,'|','|','-','-','-','-','|','|');
    wrefresh(score);

    mvwprintw(mission,1,5,"Mission");
    mvwprintw(mission,2,3,"B : ()");
    mvwprintw(mission,3,3,"+ : %d (%c)",mission_food,mission_food_complete);
    mvwprintw(mission,4,3,"- : %d (%c)",mission_poison,mission_poison_complete);
    mvwprintw(mission,5,3,"G : %d (%c)",gate_cnt,mission_gate_complete);
    wborder(mission,'|','|','-','-','-','-','|','|');
    wrefresh(mission);

        map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
        for(int i=0;i<y;i++){
            map[i]=new int[x];
        }

        //중간 벽
        for(int i=y/2-5;i<y/2+10;i++){
        mvprintw(i,x/2+1,"|"); //30
        }
        //중간- 윗벽
       for(int i =x/2-1-5;i<x/2+10;i++){
            mvprintw(y/2-5,i,"_");
        }
         wrefresh(play);

         // 벽으로(2) 설정하는 부분 필요
        // mapping  mwv (y,x)
        for(int row = 0;row< y;row++){
            for(int col = 0; col < x; col++){
                // Wall
                if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
                    map[row][col]=2;

                }
                // immune Wall
                else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                    map[row][col] = 1;
                }
                // empty space
                else{
                    map[row][col] = 0;

                }
            }
        }
    }

    else if (level == 4 ){
        mvprintw(1,20,"STAGE 4");


        max_height = 27;
        max_width = 54;
        play = newwin(max_height,max_width,3,3);
        getmaxyx(play,y,x);
        wborder(play,'x','x','x','x','x','x','x','x');

        // score window
    score = newwin(8,20,3,70);
    //  mission window
    mission = newwin(8,20,13,70);
    point  = 0;
    food_cnt = 0;
    poison_cnt = 0;
    gate_cnt = 0;
    mission_food_complete = ' '; // 미션 완료 표시
    mission_poison_complete = ' '; // 미션 완료 표시 --> 조건을 충족하면 food 나 poision 쪽에서 'v'로 바꿔줄겁니다.
    mission_gate_complete = ' ';
    body_length = INIT_LENGTH + food_cnt - poison_cnt;
    speed_interval = 15000;
    current_speed = INIT_SPEED;

    mvwprintw(score,1,4,"Score Board");
    mvwprintw(score,2,3,"B : ");
    mvwprintw(score,3,3,"+ : ");
    mvwprintw(score,4,3,"- : ");
    mvwprintw(score,5,3,"G : ");
    wborder(score,'|','|','-','-','-','-','|','|');
    wrefresh(score);

    mvwprintw(mission,1,5,"Mission");
    mvwprintw(mission,2,3,"B : ()");
    mvwprintw(mission,3,3,"+ : %d (%c)",mission_food,mission_food_complete);
    mvwprintw(mission,4,3,"- : %d (%c)",mission_poison,mission_poison_complete);
    mvwprintw(mission,5,3,"G : %d (%c)",gate_cnt,mission_gate_complete);
    wborder(mission,'|','|','-','-','-','-','|','|');
    wrefresh(mission);
        mission_food =9;
        mission_poison =4;
        mission_gate = 2;

        // 중간에 나타나는 벽 
        for(int i=y/2-5;i<y/2+10;i++){
        mvprintw(i,x/2+1,"|"); //30
        }
        // 중간 - 윗벽
       for(int i =x/2-1-5;i<x/2+10;i++){
            mvprintw(y/2-5,i,"_");
        }
        
        // 중간 - 아랫벽
       for(int i =x/2-1-5;i<x/2+10;i++){
            mvprintw(y/2+9,i,"-");
        }
        

        wrefresh(play);

        map = new int*[y];   // row 개만큼 할당 받고, 각 row마다 col개만큼 다시 할당받는다.
        for(int i=0;i<y;i++){
            map[i]=new int[x];
        }

        // mapping  mwv (y,x)
        for(int row = 0;row< y;row++){
            for(int col = 0; col < x; col++){
                // Wall
                if ((row==0 && col==0) || (row== 0 && col == x-1) || (row == y-1 && col == 0)|| (row == y-1 && col == x-1)){
                    map[row][col]=2;

                }
                // immune Wall
                else if(row == 0 || col == 0  || col == x-1 || row ==y-1 ){
                    map[row][col] = 1;
                }
                // empty space
                else{
                    map[row][col] = 0;

                }
            }
        }
    }



     

  



    
// 뭔가 먹었니?
    get = false;
    
// 독 먹었니?
    poi = false;

//게이트를 통과했니?
    enter_gate = false;

//seg fault
// snake의 시작점 , 뱀 본체 준비
// for(int i=0;i<3;i++){
//         Rsnake.push_back(snakeBody(24+i,11));  //24 가 x좌표고 ,11이 y좌표 
//     }

// 맵에 뱀을 그리는 과정
for(int i=0;i<Rsnake.size();i++){
        mvwprintw(play,Rsnake[i].y,Rsnake[i].x,"O");
        map[Rsnake[i].y][Rsnake[i].x] = 3;
    }    

//밥과 독을 놓읍시다.
    generatefood();
    generatepoison();

//초기 이동 방향
    direction='l';

//화면 업데이트
    wrefresh(play);
// 자잘한 변수들 (다음 단계에서 사용할 것들)


    // resize_term(행=row=y ,열=col=x)
    // max_height = 23 = row=y, max_width 46= col=x;
    // map[row][col] = (col,row);


    //  3,3부터 시작
    //  가로 46 ,세로 23
    //  (3,3) ~ (48,3) 가로 최대
    //  (3,3) ~ (3,25) 세로 최대
    // 뱀 초기 길이 3
    
}

snake::~snake(){
    nodelay(stdscr,false);
    getch();
    endwin();
}

// 독을 만드는 과정
void snake::generatepoison(){
    while(true){
        int poison_x = rand()%(x-4)+2;
        int poison_y = rand()%(y-4)+2;

        // 독을 만들었는데, 그게 벽 위라면? 다시 만들어라
        if ( map[poison_y][poison_x] == 1 ||map[poison_y][poison_x] == 2 ){
            continue;
        }

        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==poison_x && Rsnake[i].y == poison_y){
                continue;
            }
        }
        poison.x = poison_x;
        poison.y = poison_y;

        //이게 밥이나 독약을 map 배열에서 표시를 해야한다고 되어있긴 한데, 제 능력으로는 계속 segmentation fault가 나서 일단 보류했습니다.
        //map[food.y][food.x] = 4;
        break;
    }

    mvwprintw(play,poison.y,poison.x,"-"); // 독 추가
    wrefresh(play);  // 독 업데이트
}




void snake::generatefood(){
    
    while(true){
        int food_x = rand()%(x-4)+2;
        int food_y = rand()%(y-4)+2;
           if ( map[food_y][food_x] == 1 ||map[food_y][food_x] == 2 ){
            continue;
        }


        for(int i=0;i<Rsnake.size();i++){
            if(Rsnake[i].x==food_x && Rsnake[i].y == food_y){
                continue;
            }
        }
        food.x = food_x;
        food.y = food_y;
        
        //map[food.y][food.x] = 4;
        break;
    }

    mvwprintw(play,food.y,food.x,"+"); // 음식 추가
    wrefresh(play);  // 음식 업데이트

}


bool snake::collision(){

    
    // 벽에 부딪힌 경우
    if(map[Rsnake[0].y][Rsnake[0].x]==1){
    
        return true;
    }

    // 게이트를 통과한 경우
    if(map[Rsnake[0].y][Rsnake[0].x]==7){
        gate_cnt += 1;
        mvwprintw(score,5,3,"G : %d",gate_cnt);
        wrefresh(score);
        enter_gate = true;
        return false;
    }


    
    //뱀이 자기를 물은 경우
    for(int i=2;i<Rsnake.size();i++){
        if(Rsnake[0].x == Rsnake[i].x && Rsnake[0].y == Rsnake[i].y){
            return true;
        }
    }

    //독을 먹은 경우
    if((Rsnake[0].x==poison.x) && (Rsnake[0].y == poison.y)){

        generatepoison();
        poison_cnt+=1;
        
        body_length = INIT_LENGTH + food_cnt - poison_cnt;
        current_speed += speed_interval;
       
        if (body_length<3){
            return true;
        }

        mvwprintw(score,4,10,"%d",poison_cnt);
        mvwprintw(score,2,10,"%d",body_length); 
        wrefresh(score); // 상태창 업데이트
        
        mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," "); //화면에 보이는 꼬리부분 지우기
        map[Rsnake[Rsnake.size()-1].y][Rsnake[Rsnake.size()-1].x]=0; // map[][]에 저장된 value를 0으로 바꾸기
        Rsnake.pop_back();
        usleep(current_speed);

    }


    //밥을 먹은 경우
    if((Rsnake[0].x==food.x) && (Rsnake[0].y == food.y)){
        //map[food.y][food.x] = 3;

        generatefood(); 
        get = true;
        food_cnt+=1;
        
        body_length = INIT_LENGTH + food_cnt - poison_cnt;
        current_speed -= speed_interval;
        mvwprintw(score,2,10,"%d",body_length);
        mvwprintw(score,3,10,"%d",food_cnt);
        wrefresh(score); // 상태창 업데이트
        usleep(current_speed);
        return false;

    }
    
    else{
       get=false;
    }

    
    return false;

}

void snake::make_gate(){
    srand((unsigned int)time(0));
    int firstLayer = rand()%4;
    int secondLayer = rand()%4;

    while (1)
    {
        switch ((enum LayerType)firstLayer)
        {
        case G1:
            fgate.g_y = 1 + rand()%(max_height-4);    //gate1(0,rand)
            break;
        case G2:
            fgate.g_x = 1 + rand()%(max_width-4);    //gate2(rand,0)
            break;
        case G3:
            fgate.g_x = max_width-1;
            fgate.g_y = 1 + rand()%(max_height-4);    //gate3(max,rand)
            break;
        case G4:
            fgate.g_x = 1 + rand()%(max_width-4);    //gate4(rand,max)
            fgate.g_y = max_height-1;
            break;
        }

        switch ((enum LayerType)secondLayer)
        {
        case G1:
            sgate.g_y = 1 + rand()%(max_height-4);    //gate1(0,rand)
            break;
        case G2:
            sgate.g_x = 1 + rand()%(max_width-4);    //gate2(rand,0)
            break;
        case G3:
            sgate.g_x = max_width-1;
            sgate.g_y = 1 + rand()%(max_height-4);    //gate3(max,rand)
            break;
        case G4:
            sgate.g_x = 1 + rand()%(max_width-4);    //gate4(rand,max)
            sgate.g_y = max_height-1;
            break;
        }
        if (fgate.g_x != sgate.g_x || fgate.g_y != sgate.g_y) break;
    }

    /* set gate's value in map[][] */
    map[fgate.g_y][fgate.g_x] = 7;
    map[sgate.g_y][sgate.g_x] = 7;


    /* Set color gate */
    mvwaddch(play,fgate.g_y,fgate.g_x,'X' | A_UNDERLINE | COLOR_PAIR(1));
    mvwaddch(play,sgate.g_y,sgate.g_x,'X' | A_UNDERLINE | COLOR_PAIR(2)); // 확인을 위해 두번째 문은 초록색으로

    wrefresh(play);
}

void snake::move(){

    // 키를 입력 받습니다.
    // Rsnake에서 하나 없어질 때 마다 Tempsnake에 하나 씩 그리기
    int key = getch();

    switch(key){
        case KEY_LEFT:
			if(direction =='r'){
                flag =1;
                break;
            }
				direction='l';
			break;
		
        case KEY_UP:
			if(direction=='d'){
                flag=1;
                break;
            }
			direction='u';
			break;
		
        
        case KEY_DOWN:
			if(direction =='u'){
                flag = 1;
                break;
            }
			direction='d';
			break;
		
        
        case KEY_RIGHT:
			if(direction =='l'){
                flag =1 ;
                break;
            }
			direction='r';
			break;
		
    }

    // 벽에 부딪힌 것을 표현 하기 위해서 시도를 해봤는데, flag를 사용하는게 그나마 쉬운 것 같아서 사용했습니다.
    // flag == > 벽에 부딪혔니? --> flag가 1이면 맨 아래의 start() 함수에서 break를 통해 게임이 끝나게 됩니다.


    if(!get){
		mvwprintw(play,Rsnake[Rsnake.size()-1].y,Rsnake[Rsnake.size()-1].x," ");
        map[Rsnake[Rsnake.size()-1].y][Rsnake[Rsnake.size()-1].x] = 0;  
		Rsnake.pop_back();
        wrefresh(play);
        }
    

    //get == true 인 경우 !get == false가 되어 이부분을 스킵하고 지나갑니다. (꼬리부분이 사라지지 않고 남음 ==> 길이가 1 증가됨.)
    //get == false인 경우에는 !get == true가 되어 이부분을 수행합니다. (꼬리부분을 pop을 통해서 지웁니다. ==> 길이가 1 감소됨. )

    //gate를 통과하는 경우도 !get == ture이기 때문에 꼬리가 하나 빠집니다. 그리고 그 꼬리는 

    if(enter_gate){ //게이트를 통과한 경우

        // 근데 그게 첫번 째 문에 부딪힌 경우
        if(Rsnake[0].y == fgate.g_y && Rsnake[0].x == fgate.g_x){
            

            //두번째 문으로 나오자.
            //두번 째 문이 어디있는지 알아야 한다. (어느 모서리에 있는지)
            
            // 왼쪽 모서리
            if(sgate.g_x == 0){
                direction = 'r';  //나오는 방향은 오른쪽
                Rsnake.insert(Rsnake.begin(),snakeBody(sgate.g_x+1,sgate.g_y));
                
            }


            //오른쪽 모서리
            else if(sgate.g_x == max_width-1){
                direction = 'l';
                Rsnake.insert(Rsnake.begin(),snakeBody(sgate.g_x-1,sgate.g_y));
                
            }

            // 남은건 아래 또는 위일텐데
            // 위
            else if(sgate.g_y == 0){
                direction = 'd';
                Rsnake.insert(Rsnake.begin(),snakeBody(sgate.g_x,sgate.g_y+1));  
            }

            //아래
            else if(sgate.g_y == max_height-1){
                direction = 'u';
                Rsnake.insert(Rsnake.begin(),snakeBody(sgate.g_x,sgate.g_y-1));  
            }

        }
        // 두번째 문에 부딪힌 경우
        else if(Rsnake[0].y == sgate.g_y && Rsnake[0].x == sgate.g_x){
            //첫번째 문으로 나오자.
            // 왼쪽 모서리
            if(fgate.g_x ==0){
                direction = 'r';
                Rsnake.insert(Rsnake.begin(),snakeBody(fgate.g_x+1,fgate.g_y));
                
            }


            //오른쪽 모서리
            else if(fgate.g_x == max_width-1){
                direction = 'l';
                Rsnake.insert(Rsnake.begin(),snakeBody(fgate.g_x-1,fgate.g_y));
            }

            // 남은건 아래 또는 위일텐데
            // 위
            else if(fgate.g_y == 0){
                direction = 'd';
                Rsnake.insert(Rsnake.begin(),snakeBody(fgate.g_x,fgate.g_y+1));
            }

            //아래
            else if(fgate.g_y == max_height-1){
                direction = 'u';
                Rsnake.insert(Rsnake.begin(),snakeBody(fgate.g_x,fgate.g_y-1));
            }
        }


    }else{
        //아래 부분에서 하나 빠진 꼬리를 다시 헤드로 붙여줍니다. (Rsnake[0]이 바뀌게 됨)
        if(direction=='l')
	    {
		    Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x-1,Rsnake[0].y));
            if(map[Rsnake[0].y][Rsnake[0].x]==1){
                flag = 1;
            }
	    }else if(direction=='r'){
		    Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x+1,Rsnake[0].y));
            if(map[Rsnake[0].y][Rsnake[0].x]==1){
                flag = 1;
            }

	    }else if(direction=='u'){
		    Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y-1));
            if(map[Rsnake[0].y][Rsnake[0].x]==1){
                flag = 1;

            }

	    }else if(direction=='d'){
	        	Rsnake.insert(Rsnake.begin(),snakeBody(Rsnake[0].x,Rsnake[0].y+1));
                if(map[Rsnake[0].y][Rsnake[0].x]==1){
                    flag = 1;
                }
     
	    }


    }
    //상태를 업데이트 합니다.
        mvwprintw(play,Rsnake[0].y,Rsnake[0].x,"O");
        

        /* set gate's value in map[][] */
        map[fgate.g_y][fgate.g_x] = 7;
        map[sgate.g_y][sgate.g_x] = 7;


        //일부 미션을 완료하면 v표시로 바뀝니다.
        if (food_cnt == mission_food){
            mission_food_complete = 'v';
            mvwprintw(mission,3,3,"+ : %d (%c)",mission_food,mission_food_complete);
            
        }
        if(poison_cnt == mission_poison){
            mission_poison_complete='v';
            mvwprintw(mission,4,3,"- : %d (%c)",mission_poison,mission_poison_complete);
        }
        if(gate_cnt >= mission_gate){
            mission_gate_complete='v';
            mvwprintw(mission,5,3,"- : %d (%c)",mission_gate,mission_gate_complete);

        }

        

        wrefresh(mission);
        wrefresh(play);

        enter_gate =false;
    



}
//현재버그 
// 1) 좌 우 모서리에 게이트가 생기는 경우만 통과할 수 있음 (해결)
// 2) 한번 통과하면 게이트가 사라짐 (map정보는 업데이트를 해서 계속 왔다 갔다 할 수 있습니다. 여유있으시면 슬쩍 고쳐주세요.)
// 3) 통과할 때 몸체가 하나 붙음 (실제로 붙는건 아니고 화면 상에서만 하나 더 붙음) (해결)  

bool snake::mission_clear(){
    if (mission_food == food_cnt && mission_poison == poison_cnt && mission_gate == gate_cnt){
        return true;
    }
    return false;
}

int snake::start(){
    make_gate();

    while(true){   
        if(collision()){
            wattron(play,COLOR_PAIR(1));
            mvwprintw(play,10,19,"G A M E O V E R");
            wrefresh(play);
            break;
        }
        move();
        
        if (flag==1){
            wattron(play, COLOR_PAIR(1));
            mvwprintw(play,10,19,"G A M E O V E R");
            wrefresh(play);
            break;
        }

        if(mission_clear()){
            mvwprintw(play,10,19,"S T A G E C L E A R !");
            wrefresh(play);
            //잠시 쉽시다.
            usleep(3300000);
            return 1;
        }
        //flag initialize
        flag =0;

        //usleep 값에따라 지렁이 속도가 달라집니다. 원하시는 대로 설정 해주세요.
        usleep(current_speed);
    }
    return 0;
    
       
}

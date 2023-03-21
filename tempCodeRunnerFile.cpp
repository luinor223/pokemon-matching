for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++)  //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j;
        }
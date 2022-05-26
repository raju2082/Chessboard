#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class chessBoard {

    private:
        /*! Individual square box info */
        struct square {
            unsigned int height;
            bool marked;
        };
        typedef struct square square_t;
        /*! num of square in a given board */
        unsigned int numSquares = 0;
        /*! maximum rows and maximum columns in a given board */
        unsigned int maxRow, maxCol;
        /*! maximum height in a given board */
        unsigned int maxHeight = 0;

        /*!
         * @fn      findVolumeOfSquares()
         * @brief   recursively finds the volume of square connected to each other.
         * @public
         *
         * @param [IN]  *ele    array of individual square boxes
         * @param [IN]  cRow    current row
         * @param [IN]  cCol    current column
         * @param [OUT] sum     sum of volume of connected squares
         * @param [OUT] drained to store drain status of given connected square
         *
         * @retval "nothing". 
         */
        void findVolumeOfSquares(square_t *ele, unsigned int cRow, unsigned int cCol, unsigned int &sum, bool &drained);
    public:
       
        /*! used to store board valid status */
        bool isBoardValid = false;
        /*! used to store total volume of board */
        unsigned int totalVolume = 0;

        /*!
         * @fn      findVolumeOfBoard()
         * @brief   finds the volume of board.
         * @public
         *
         * @param [IN]  *board  row-major array of board
         *
         * @retval "totalVolume of board".
         */
        unsigned int findVolumeOfBoard(unsigned int *board);

        /*!
         * @fn      chessBoard()
         * @brief   constructor to initialize board.
         * @public
         *
         * @param [IN]  *board  row-major array of board
         * @param [IN]  maxRow  max rows on the board
         * @param [IN]  maxCol  max columns on the board
         *
         * @retval "nothing". 
         */
        chessBoard(unsigned int *board, unsigned int maxRow, unsigned int maxCol);
        /*! destructor */
        ~chessBoard();
};

/*!
 * @fn      findVolumeOfSquares()
 * @brief   recursively finds the volume of square connected to each other.
 * @public
 *
 * @param [IN]  *ele    array of individual square boxes
 * @param [IN]  cRow    current row
 * @param [IN]  cCol    current column
 * @param [OUT] sum     sum of volume of connected squares
 * @param [OUT] drained to store drain status of given connected square
 *
 * @retval "nothing". 
 */
void chessBoard::findVolumeOfSquares(square_t *ele, unsigned int cRow, unsigned int cCol, unsigned int &sum, bool &drained)
{
    unsigned int indexOfSquare = (cRow * maxCol) + cCol;
    square_t& square = ele[indexOfSquare];

#if 1
    if((square.height == 0) && (!square.marked))
    {
        square.marked = true;
        if((cCol == 0) || ((cCol + 1) == maxCol) || (cRow == 0) || ((cRow + 1) == maxRow))
        {
            drained = true;
            sum = 0;
        }

        if(drained != true)
        {
            sum = sum + 1;
        }

        /*! recursively calculate volume of square */
        if(cCol < (maxCol - 1))
            findVolumeOfSquares(ele, cRow, cCol+1, sum, drained);
        if(cCol > 0)
            findVolumeOfSquares(ele, cRow, cCol-1, sum, drained);
        if(cRow < (maxRow - 1))
            findVolumeOfSquares(ele, cRow+1, cCol, sum, drained);
        if(cRow > 0)
            findVolumeOfSquares(ele, cRow-1, cCol, sum, drained);
    }
#endif

}

/*!
 * @fn      findVolumeOfBoard()
 * @brief   finds the volume of board.
 * @public
 *
 * @param [IN]  *b  row-major array of board
 *
 * @retval "totalVolume of board".
 */
unsigned int chessBoard::findVolumeOfBoard(unsigned int *b)
{
    unsigned int i,j;
    square_t element[numSquares];

    /* calculate volume of board for each height level and add them */
    for(i = 0; i < maxHeight; i++)
    {
        unsigned int curLevelVolume = 0;
        /*! decrement height of each individual square on main board
         *  assign individual square with height 1 or 0 (0 being valley)
         */
        for(j = 0; j < numSquares; j++)
        {
            if(b[j] > 0)
            {
                b[j] = b[j] - 1;
                element[j].height = 1;
            }
            else
            {
                element[j].height = 0;
            }
            element[j].marked = false;
        }

        unsigned int cRow;
        unsigned int cCol;
        /*! calculate volume for every square of the current height level and add them */
        for(cRow = 0; cRow < maxRow; cRow++)
        {
            for(cCol = 0; cCol < maxCol; cCol++)
            {
                unsigned int sum = 0;
                bool drained = false;

                findVolumeOfSquares(element, cRow, cCol, sum, drained);
                curLevelVolume = curLevelVolume + sum;
            }
        }
        totalVolume = totalVolume + curLevelVolume;
    }
    return totalVolume;
}

/*!
 * @fn      chessBoard()
 * @brief   constructor to initialize board.
 * @public
 *
 * @param [IN]  *board  row-major array of board
 * @param [IN]  maxRow  max rows on the board
 * @param [IN]  maxCol  max columns on the board
 *
 * @retval "nothing". 
 */
chessBoard::chessBoard(unsigned int *board, unsigned int maxRow, unsigned int maxCol)
{
    if(!board) {
        isBoardValid = false;
        cout<< "Invalid board data" <<endl;
        return;
    }
   
    /*! input rows and columns must be greater than 3 */
    if((maxRow < 3) || (maxCol < 3)) {
        isBoardValid = false;
        cout<< "Invalid size: Please provide row and column greater than 3" <<endl;
        return;
    }

    isBoardValid = true;

    this->maxRow = maxRow;
    this->maxCol = maxCol; 

    numSquares = maxRow * maxCol;

    /* find max height present on the board */
    unsigned int i;
    for(i = 0; i < numSquares; i++) {
        if(maxHeight < board[i])
            maxHeight = board[i];
    }
    return;
}

chessBoard::~chessBoard()
{
    return; 
}

int main(int argc, char* argv[])
{
    if(argc < 4) {
        printf("please provide valid arguments:\n");
        printf("usage: ./calcVolume [row] [column] <board.txt>\n");
        return 0;
    }
   
    unsigned int row_max = stoi(argv[1]);
    unsigned int col_max = stoi(argv[2]);
    unsigned int n = row_max * col_max ;

    string *myArray = new string[n];
    unsigned int *chboard = new unsigned int[n];
    ifstream file(argv[3]);
    if(file.is_open())
    {
        for(int i = 0; i < n; ++i)
        {
            file >> myArray[i];
        }
        for(int i = 0; i < n; ++i)
        {
            chboard[i] = stoi(myArray[i]);
        }
        /*! initialize chess board */
        chessBoard cBoard(chboard, row_max, col_max);

        if(cBoard.isBoardValid) {
            unsigned int tVol = cBoard.findVolumeOfBoard(chboard);
            printf("Total Volume of Board = %d\n", tVol);
        }
    } else {
        cout<<"Invalid file"<<endl;
    }

    return 0;
}

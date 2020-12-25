#include <windows.h>
#include <time.h>

#define CL_BLACK RGB(0, 0, 0)
#define CL_WHITE RGB(255,255,255)
#define CL_LIGHTGRAY RGB(211,211,211)
#define CL_SILVER RGB(192, 192, 192)
#define CL_GRAY RGB(128, 128, 128)
#define CL_DARKGRAY RGB(105, 105, 105)
#define CL_BLUE RGB(0, 0, 255)
#define CL_GREEN RGB(0, 255, 0)
#define CL_RED RGB(255, 0, 0)
#define CL_YELLOW RGB(255, 255, 0)
#define CL_AQUA RGB(0, 255, 255)
#define CL_LIGHTGREEN RGB(0, 218, 81)
#define CL_DARKGREEN RGB(0, 100, 0)
#define CL_SKYBLUE RGB(135, 206, 250)
#define CL_MIDNIGHTBLUE RGB(25, 25, 112)
#define CL_BROWN RGB(139, 69, 19)

static const float PI = 3.14;
static const int winWidth = 1800;
static const int winHeight = 800;

POINT planetPos;
POINT stars[300];
POINT cloudPos[8];
COLORREF skyGradient[500];
COLORREF fieldGradient[500];
COLORREF cloudColor[8];
int curSkyColorIndex = 0;
int numOfSkyColors = 0;
int curFieldColorIndex = 0;
int numOfFieldColors = 0;
int isNight = 0;
int curMaxCloudIndex = 0;

void PaintRect(HDC, COLORREF, int, int, int, int);
void PaintEllipse(HDC, COLORREF, int, int, int, int);
void PaintCircle(HDC, COLORREF, int, int, int);
void PaintLine(HDC, COLORREF, int, int, int, int, int);
void PaintPolygon(HDC, COLORREF, POINT*, int);

void PaintBG(HDC);
void PaintMoon(HDC);
void PaintSky(HDC);
void PaintStarsInSky(HDC, int);
void PaintField(HDC);
void PaintCloud(HDC, int);

void GenerateCloud();
void GenerateStars();
void GenerateGradient(COLORREF, COLORREF, COLORREF gradient[]);
void ProcessClouds();


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int x, y;

char szClassName[] = "CG_WAPI_Template";


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	// Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	

	// Регистрируем класс окна
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Не удалось зарегестрировать класс окна!", "Ошибка", MB_OK);
		return 0;
	}
	// Создаем основное окно приложения
	hWnd = CreateWindow(
		szClassName,                // Имя класса                   
		"SKY",                      // Текст заголовка
		WS_OVERLAPPEDWINDOW,        // Стиль окна                                             
		0, 0,                     // Позиция левого верхнего угла  
		winWidth, winHeight,        // Ширина и высота окна    
		(HWND)NULL,                 // Указатель на родительское окно NULL    
		(HMENU)NULL,                // Используется меню класса окна              
		(HINSTANCE)hInstance,       // Указатель на текущее приложение
		NULL
	);                      // Передается в качестве lParam в событие WM_CREATE
	if (!hWnd)
	{
		MessageBox(NULL, "Не удалось создать главное окно!", "Ошибка", MB_OK);
		return 0;
	}
	// Показываем наше окно
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
    PAINTSTRUCT  ps;
	HDC          hdc;

	planetPos.x = -75;
	planetPos.y = 100;

	GenerateCloud();
	GenerateGradient(CL_SKYBLUE, CL_MIDNIGHTBLUE, skyGradient);
	int i = 0;
	while (skyGradient[i] != 0) {
		i++;
	}
	numOfSkyColors = i - 1;
	GenerateGradient(CL_LIGHTGREEN, CL_DARKGREEN, fieldGradient);
	i = 0;
	while (fieldGradient[i] != 0) {
		i++;
	}
	numOfFieldColors = i - 1;
	GenerateStars();

	SetTimer(hWnd, 1, 45, NULL);
	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);		
	}
	return (lpMsg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
						 WPARAM wParam, LPARAM lParam)
{
	//Цикл обработки сообщений
	switch (messg)
	{

	//Сообщение таймера
	case WM_TIMER:
	{
		HDC hdc = GetDC(hWnd);
		HDC hMemDC = CreateCompatibleDC(hdc);
		HBITMAP hMemBmp = CreateCompatibleBitmap(hdc, winWidth, winHeight);
		HBITMAP hOldMemBmp = (HBITMAP)SelectObject(hMemDC, hMemBmp);


		PaintBG(hMemDC);

		BitBlt(hdc, 0, 0, winWidth, winHeight, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOldMemBmp);
		DeleteObject(hMemBmp);
		DeleteDC(hMemDC);
	}
		break;
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
	}
	return 0;
}

void GenerateStars() {
	srand(time(NULL));
	for (int i = 0; i < sizeof(stars)/sizeof(POINT); i++) {
		stars[i].x = rand() % winWidth;
		stars[i].y = rand() % winHeight/3*2;
	}
}

void GenerateGradient(COLORREF beginColor, COLORREF endColor, COLORREF gradient[]) {
	if (beginColor > endColor) {
		COLORREF buff = beginColor;
		beginColor = endColor;
		endColor = buff;
	}
	gradient[0] = beginColor;
	
	byte endBlue = GetBValue(endColor);
	byte endRed = GetRValue(endColor);
	byte endGreen = GetGValue(endColor);
	int i = 1;
	while (gradient[i-1] != endColor) {
		gradient[i] = gradient[i - 1];
		if (GetBValue(gradient[i]) != endBlue) {
			gradient[i] += RGB(0, 0, 1);
		}
		if (GetGValue(gradient[i]) != endGreen) {
			gradient[i] += RGB(0, 1, 0);
		}
		if (GetRValue(gradient[i]) != endRed) {
			gradient[i] += RGB(1, 0, 0);
		}
		i++;
	}
}

void GenerateCloud() {
	cloudPos[curMaxCloudIndex].x = winWidth - 100;
	cloudPos[curMaxCloudIndex].y = rand() % (winHeight / 4) + 40;

	cloudColor[curMaxCloudIndex] = rand() % 2 == 0 ? CL_LIGHTGRAY : CL_WHITE;

	if (curMaxCloudIndex != 0) {
		cloudPos[curMaxCloudIndex].y = (cloudPos[curMaxCloudIndex - 1].y + rand() % (winHeight / 4)) / 2 + 40;
	}
	else {
		cloudPos[curMaxCloudIndex].y = (cloudPos[curMaxCloudIndex].y + rand() % (winHeight / 4)) / 2 + 40;
	}

	curMaxCloudIndex++;
}

void ProcessClouds() {
	for (int i = 0; i < curMaxCloudIndex; i++) {
		cloudPos[i].x -= 2* winWidth / numOfSkyColors;
	}
}

void PaintRect(HDC hdc, COLORREF color, int x1, int y1, int x2, int y2) {
	RECT rect;
	rect.left = x1;
	rect.right = x2;
	rect.top = y1;
	rect.bottom = y2;

	HBRUSH hBrush = CreateSolidBrush(color);
	FillRect(hdc, &rect, hBrush);

	DeleteObject(hBrush);
}

void PaintEllipse(HDC hdc, COLORREF color, int x1, int y1, int x2, int y2) {
	HPEN hPen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);
	
	
	Ellipse(hdc, x1, y1, x2, y2);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void PaintCircle(HDC hdc, COLORREF color, int radius, int xCenter, int yCenter) {
	HPEN hPen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);

	Ellipse(hdc, xCenter-radius, yCenter-radius, xCenter+radius, yCenter+radius);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void PaintLine(HDC hdc, COLORREF color, int lineDepth, int x1, int y1, int x2, int y2) {
	HPEN hPen = CreatePen(PS_SOLID, lineDepth, color);
	SelectObject(hdc, hPen);

	MoveToEx(hdc, x1, y1, NULL);	
	LineTo(hdc, x2, y2);

	DeleteObject(hPen);
}

void PaintPolygon(HDC hdc, COLORREF color, POINT* points, int pointsCount) {
	HPEN hPen = CreatePen(PS_SOLID, 0, color);
	SelectObject(hdc, hPen);
	HBRUSH hBrush = CreateSolidBrush(color);
	SelectObject(hdc, hBrush);

	Polygon(hdc, points, pointsCount);

	DeleteObject(hPen);
	DeleteObject(hBrush);
}

void PaintMoon(HDC hdc) {
	PaintCircle(hdc, CL_SILVER, 75, planetPos.x, planetPos.y);

	PaintCircle(hdc, CL_DARKGRAY, 18, planetPos.x + 40, planetPos.y - 5);
	PaintCircle(hdc, CL_DARKGRAY, 10, planetPos.x + 20, planetPos.y - 2);
	PaintCircle(hdc, CL_GRAY, 14, planetPos.x, planetPos.y);
	PaintCircle(hdc, CL_GRAY, 9, planetPos.x + 5, planetPos.y - 10);
	PaintCircle(hdc, CL_GRAY, 13, planetPos.x + 20, planetPos.y - 15);
	PaintCircle(hdc, CL_GRAY, 10, planetPos.x + 10, planetPos.y - 22);
	PaintCircle(hdc, CL_GRAY, 10, planetPos.x - 15, planetPos.y + 5);


	PaintCircle(hdc, CL_DARKGRAY, 15, planetPos.x, planetPos.y + 50);
	PaintCircle(hdc, CL_DARKGRAY, 5, planetPos.x - 10, planetPos.y + 60);
	PaintCircle(hdc, CL_DARKGRAY, 11, planetPos.x + 30, planetPos.y + 55);
	PaintCircle(hdc, CL_GRAY, 10, planetPos.x + 23, planetPos.y + 33);
	PaintCircle(hdc, CL_GRAY, 15, planetPos.x + 18, planetPos.y + 45);


	PaintCircle(hdc, CL_DARKGRAY, 15, planetPos.x - 30, planetPos.y - 40);
	PaintCircle(hdc, CL_GRAY, 10, planetPos.x - 40, planetPos.y - 33);
	PaintCircle(hdc, CL_GRAY, 7, planetPos.x - 15, planetPos.y - 44);
	PaintCircle(hdc, CL_GRAY, 5, planetPos.x - 20, planetPos.y - 60);


	PaintCircle(hdc, CL_GRAY, 10, planetPos.x - 50, planetPos.y);
	PaintCircle(hdc, CL_GRAY, 8, planetPos.x - 45, planetPos.y + 10);
	PaintCircle(hdc, CL_GRAY, 7, planetPos.x - 50, planetPos.y + 20);
}

void PaintCloud(HDC hdc, int index) {
	PaintEllipse(hdc, cloudColor[index], cloudPos[index].x + 40, cloudPos[index].y - 20, cloudPos[index].x - 40, cloudPos[index].y + 10);
	PaintEllipse(hdc, cloudColor[index], cloudPos[index].x + 15, cloudPos[index].y - 10, cloudPos[index].x - 15, cloudPos[index].y - 25);
	PaintEllipse(hdc, cloudColor[index], cloudPos[index].x + 20, cloudPos[index].y, cloudPos[index].x - 20, cloudPos[index].y + 15);
}

void PaintStarsInSky(HDC hdc, int numOfStars) {
	srand(time(NULL));
	int starColor;
	for (int i = 0; i < numOfStars; i++) {
		starColor = rand() % 10;
		switch (starColor) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			SetPixel(hdc, stars[i].x, stars[i].y, CL_WHITE);
			break;
		case 7:
			SetPixel(hdc, stars[i].x, stars[i].y, CL_LIGHTGRAY);
			break;
		case 8:
			SetPixel(hdc, stars[i].x, stars[i].y, CL_YELLOW);
			break;
		case 9:
			SetPixel(hdc, stars[i].x, stars[i].y, CL_BLUE);
			break;
		}
	}
}

void PaintSky(HDC hdc) {
	static int numOfStars;
	int planetStep = (winWidth+150) /numOfSkyColors;

	if (!isNight) {
		if (planetPos.x > winWidth / 2) {
			if (curSkyColorIndex < numOfSkyColors) {
				curSkyColorIndex++;
			}
		}
		else {
			if (curSkyColorIndex > numOfSkyColors/2) {
				curSkyColorIndex--;
			}
		}
	}
	else {
		if (planetPos.x > winWidth / 2) {
			if (curSkyColorIndex > 0) {
				curSkyColorIndex--;		
			}
			if (numOfStars < sizeof(stars) / sizeof(POINT)) {
				numOfStars += 5;
			}
		}
		else {
			if (curSkyColorIndex < numOfSkyColors / 2) {
				curSkyColorIndex++;
			}
			if (numOfStars >= 3) {
				numOfStars -= 3;
			}
		}
	}
	
	PaintRect(hdc, skyGradient[curSkyColorIndex], 0, 0, winWidth, winHeight);
	if (planetPos.x <= -75) {
		isNight = !isNight;
		for (int i = 0; i < curMaxCloudIndex; i++) {
			cloudPos[i].x = -75;
		}
		if (isNight) {
			numOfStars = 1;
		}
		else {
			curMaxCloudIndex = 0;
		}
		planetPos.x = winWidth + 75;
	}
	else {
		planetPos.x -= planetStep;
		if (isNight) {
			PaintStarsInSky(hdc, numOfStars);
			PaintMoon(hdc);
		}
		else {
			if (curMaxCloudIndex < 8 && rand()%5 == 0) {
				GenerateCloud();
			}
			PaintCircle(hdc, CL_YELLOW, 75, planetPos.x, planetPos.y);
			ProcessClouds();
			for (int i = 0; i < curMaxCloudIndex; i++) {
				PaintCloud(hdc, i);
			}
		}
	}
}

void PaintField(HDC hdc) {
	POINT points[4] = { {0,winHeight}, {0,winHeight / 3 * 2}, {winWidth, winHeight / 2}, {winWidth, winHeight} };

	if (!isNight) {
		if (planetPos.x > winWidth / 2) {
			if (curFieldColorIndex < numOfFieldColors) {
				curFieldColorIndex++;
			}
		}
		else {
			if (curFieldColorIndex > numOfFieldColors / 2) {
				curFieldColorIndex--;
			}
		}
	}
	else {
		if (planetPos.x > winWidth / 2) {
			if (curFieldColorIndex > 0) {
				curFieldColorIndex--;
			}
		}
		else {
			if (curFieldColorIndex < numOfFieldColors / 2) {
				curFieldColorIndex++;
			}
		}
	}

	PaintPolygon(hdc, fieldGradient[curFieldColorIndex], points, 4);
}

void PaintBG(HDC hdc) {
	PaintSky(hdc);
	PaintField(hdc);
}
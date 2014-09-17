//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <shaders.h>

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera z pliku i jego kompilacja,
// rodzaj shadera okre�la parametr type; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadShader( GLenum type, const char *name )
{
    // odczyt kodu shadera do bufora
    std::ifstream file;
    file.open( name, std::ios::binary );
    if( file.bad() )
    {
        std::cout << "Niepoprawny odczyt pliku shadera " << name << std::endl;
        exit( 0 );
    }
    file.seekg( 0, std::ios::end );
    int len = file.tellg();
    file.seekg( 0, std::ios::beg );
    GLchar *srcBuf = new GLchar[(len + 1) * sizeof( GLchar )];
    file.read( srcBuf, len );
    srcBuf[len] = '\0';
    file.close();

    // utworzenie obiektu shadera
    GLuint shader = glCreateShader( type );

    // za�adowanie kodu do obiektu shadera
    glShaderSource( shader, 1, const_cast<const GLchar**>( &srcBuf ), NULL );

    // porz�dki
    delete[] srcBuf;

    // kompilacja shadera
    glCompileShader( shader );

    // sprawdzenie statusu kompilacji shadera
    GLint status;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        std::cout << "Niepoprawna kompilacja shadera " << name << std::endl;

        // pobranie i wy�wietlenie komunikatu b��du
        GLint logLength;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
        char *log = new char[logLength];
        glGetShaderInfoLog( shader, logLength, NULL, log );
        std::cout << log;
        delete[] log;
        exit( 0 );
    }

    // zwr�cenie identyfikatora obiektu shadera
    return shader;
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera i jego kompilacja,
// rodzaj shadera okre�la parametr type; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadShader( GLenum type, const char **src )
{
    // utworzenie obiektu shadera
    GLuint shader = glCreateShader( type );

    // za�adowanie kodu do obiektu shadera
    glShaderSource( shader, 1, src, NULL );

    // kompilacja shadera
    glCompileShader( shader );

    // sprawdzenie statusu kompilacji shadera
    GLint status;
    glGetShaderiv( shader, GL_COMPILE_STATUS, &status );
    if( status != GL_TRUE )
    {
        std::cout << "Niepoprawna kompilacja shadera" << std::endl;

        // pobranie i wy�wietlenie komunikatu b��du
        GLint logLength;
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
        char *log = new char[logLength];
        glGetShaderInfoLog( shader, logLength, NULL, log );
        std::cout << log;
        delete[] log;
        exit( 0 );
    }

    // zwr�cenie identyfikatora obiektu shadera
    return shader;
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera wierzcho�k�w z pliku
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadVertexShader( const char *name )
{
    return LoadShader( GL_VERTEX_SHADER, name );
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera wierzcho�k�w
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadVertexShader( const char **src )
{
    return LoadShader( GL_VERTEX_SHADER, src );
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera fragment�w z pliku
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadFragmentShader( const char *name )
{
    return LoadShader( GL_FRAGMENT_SHADER, name );
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera fragment�w
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadFragmentShader( const char **src )
{
    return LoadShader( GL_FRAGMENT_SHADER, src );
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera geometrii z pliku
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadGeometryShader( const char *name )
{
    return LoadShader( GL_GEOMETRY_SHADER, name );
}

//////////////////////////////////////////////////////////////////////
// za�adowanie kodu �r�d�owego shadera geometrii
// i jego kompilacja; funkcja zwraca identyfikator
// obiektu shadera ze skompilowanym shaderem
//////////////////////////////////////////////////////////////////////
GLuint LoadGeometryShader( const char **src )
{
    return LoadShader( GL_GEOMETRY_SHADER, src );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie obiektu shadera z obiektem programu;
// w razie potrzeby tworzony jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachShader( GLuint &program, GLuint shader )
{
    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera wierzcho�k�w, reprezentowanego przez kod
// �r�d�owy w pliku, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexShader( GLuint &program, const char *name )
{
    // odczyt kodu shadera z pliku i jego kompilacja
    GLuint shader = LoadVertexShader( name );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera wierzcho�k�w, reprezentowanego przez kod
// �r�d�owy, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexShader( GLuint &program, const char **src )
{
    // odczyt kodu shadera i jego kompilacja
    GLuint shader = LoadVertexShader( src );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera fragment�w, reprezentowanego przez kod
// �r�d�owy w pliku, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachFragmentShader( GLuint &program, const char *name )
{
    // odczyt kodu shadera z pliku i jego kompilacja
    GLuint shader = LoadFragmentShader( name );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera fragment�w, reprezentowanego przez kod
// �r�d�owy, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachFragmentShader( GLuint &program, const char **src )
{
    // odczyt kodu shadera i jego kompilacja
    GLuint shader = LoadFragmentShader( src );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera geometrii, reprezentowanego przez kod
// �r�d�owy w pliku, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachGeometryShader( GLuint &program, const char *name )
{
    // odczyt kodu shadera z pliku i jego kompilacja
    GLuint shader = LoadGeometryShader( name );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera geometrii, reprezentowanego przez kod
// �r�d�owy, z obiektem programu; w razie potrzeby tworzony
// jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachGeometryShader( GLuint &program, const char **src )
{
    // odczyt kodu shadera i jego kompilacja
    GLuint shader = LoadGeometryShader( src );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiektu shadera do obiektu programu
    glAttachShader( program, shader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera wierzcho�k�w i shadera fragment�w,
// reprezentowanego przez kod �r�d�owy w plikach, z obiektem programu;
// w razie potrzeby tworzony jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexFragmentShader( GLuint &program, const char *vsName, const char *fsName )
{
    // odczyt kodu shadera wierzcho�k�w z pliku i jego kompilacja
    GLuint vShader = LoadVertexShader( vsName );

    // odczyt kodu shadera fragment�w z pliku i jego kompilacja
    GLuint fShader = LoadFragmentShader( fsName );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiekt�w shader�w do obiektu programu
    glAttachShader( program, vShader );
    glAttachShader( program, fShader );
}

// powi�zanie shadera wierzcho�k�w i shadera fragment�w,
// reprezentowanego przez kod �r�d�owy, z obiektem programu;
// w razie potrzeby tworzony jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexFragmentShader( GLuint &program, const char **vsSrc, const char **fsSrc )
{
    // odczyt kodu shadera wierzcho�k�w i jego kompilacja
    GLuint vShader = LoadVertexShader( vsSrc );

    // odczyt kodu shadera fragment�w i jego kompilacja
    GLuint fShader = LoadFragmentShader( fsSrc );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiekt�w shader�w do obiektu programu
    glAttachShader( program, vShader );
    glAttachShader( program, fShader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera wierzcho�k�w, shadera geometrii i shadera
// fragment�w, reprezentowanego przez kod �r�d�owy w plikach, z obiektem
// programu; w razie potrzeby tworzony jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexGeometryFragmentShader( GLuint &program, const char *vsName, const char *gsName, const char *fsName )
{
    // odczyt kodu shadera wierzcho�k�w z pliku i jego kompilacja
    GLuint vShader = LoadVertexShader( vsName );

    // odczyt kodu shadera geometrii z pliku i jego kompilacja
    GLuint gShader = LoadGeometryShader( gsName );

    // odczyt kodu shadera fragment�w z pliku i jego kompilacja
    GLuint fShader = LoadFragmentShader( fsName );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiekt�w shader�w do obiektu programu
    glAttachShader( program, vShader );
    glAttachShader( program, gShader );
    glAttachShader( program, fShader );
}

//////////////////////////////////////////////////////////////////////
// powi�zanie shadera wierzcho�k�w, shadera geometrii i shadera
// fragment�w, reprezentowanego przez kod �r�d�owy, z obiektem
// programu; w razie potrzeby tworzony jest nowy obiekt programu
//////////////////////////////////////////////////////////////////////
void AttachVertexGeometryFragmentShader( GLuint &program, const char **vsSrc, const char **gsSrc, const char **fsSrc )
{
    // odczyt kodu shadera wierzcho�k�w i jego kompilacja
    GLuint vShader = LoadVertexShader( vsSrc );

    // odczyt kodu shadera geometrii i jego kompilacja
    GLuint gShader = LoadGeometryShader( gsSrc );

    // odczyt kodu shadera fragment�w i jego kompilacja
    GLuint fShader = LoadFragmentShader( fsSrc );

    // w razie potrzeby tworzymy obiekt programu
    if( !glIsProgram( program ) )
        program = glCreateProgram();

    // do��czenie obiekt�w shader�w do obiektu programu
    glAttachShader( program, vShader );
    glAttachShader( program, gShader );
    glAttachShader( program, fShader );
}

//////////////////////////////////////////////////////////////////////
// konsolidacja i walidacja obiektu programu
//////////////////////////////////////////////////////////////////////
void LinkProgram( GLuint program )
{
    // konsolidacja shader�w
    glLinkProgram( program );

    // sprawdzenie poprawno�ci konsolidacji shader�w
    GLint status;
    glGetProgramiv( program, GL_LINK_STATUS, &status );
    if( status == GL_FALSE )
    {
        std::cout << "Niepoprawna konsolidacja programu" << std::endl;

        // pobranie i wy�wietlenie komunikatu b��du
        GLint logLength;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
        char *log = new char[logLength];
        glGetProgramInfoLog( program, logLength, NULL, log );
        std::cout << log;
        delete[] log;
        exit( 0 );
    }

    // walidacja shader�w
    glValidateProgram( program );

    // sprawdzenie poprawno�ci walidacji shader�w
    glGetProgramiv( program, GL_VALIDATE_STATUS, &status );
    if( status == GL_FALSE )
    {
        std::cout << "Niepoprawna konsolidacja programu" << std::endl;

        // pobranie i wy�wietlenie komunikatu b��du
        GLint logLength;
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLength );
        char *log = new char[logLength];
        glGetProgramInfoLog( program, logLength, NULL, log );
        std::cout << log;
        delete[] log;
        exit( 0 );
    }
}

//////////////////////////////////////////////////////////////////////
// usuni�cie obiekt�w shadera z obiektu programu
//////////////////////////////////////////////////////////////////////
void DeleteShaders( GLuint program )
{
    // pobranie informacji o ilo�ci obiekt�w shadera
    // do��czonych do obiektu programu
    GLint maxCount;
    glGetProgramiv( program, GL_ATTACHED_SHADERS, &maxCount );

    // pobranie identyfikator�w obiekt�w shadera i ich usuni�cie
    if( maxCount != 0 )
    {
        GLuint *shaders = new GLuint[maxCount];
        glGetAttachedShaders( program, maxCount, NULL, shaders );
        for( int i = 0; i < maxCount; i++ )
            glDeleteShader( shaders[i] );
        delete[] shaders;
    }
}

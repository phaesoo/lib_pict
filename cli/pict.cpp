/* Define __cdecl for non-Microsoft compilers */
#if ( !defined(_MSC_VER) && !defined(__cdecl) )
#define __cdecl
#endif

#include <ctime>
using namespace std;

#include "cmdline.h"
#include "gcd.h"
using namespace pictcli_gcd;

#include "../include/TextEncodingDetect/text_encoding_detect.h"

using namespace AutoIt::Text;
//
//
//
void printTimeDifference( time_t start, time_t end )
{
    int diff = static_cast<int> ( difftime( end, start ) );

    // hours
    int hrs = diff / 3600;
    wcout << hrs << L":";

    // minutes
    diff -= hrs * 3600;
    int mins = diff / 60;
    wcout << ( mins < 10 ? L"0" : L"" ) << mins << L":";

    // seconds
    diff -= mins * 60;
    wcout << ( diff < 10 ? L"0" : L"" ) << diff;

    wcout << endl;
}

//
//
//
int __cdecl wmain
    (
    IN int      argc,
    IN wchar_t* args[]
    )
{
	/////////////////////////////////////////////
	if (argc != 2)
	{
		wprintf(L"\nUsage: %s filename.", args[0]);
		return 1;
	}

	// Open file in binary mode
	FILE *file = _wfopen(args[1], L"rb");

	if (file == NULL)
	{
		wprintf(L"\nCould not open file.\n");
		return 1;
	}



	// Detect the encoding
	TextEncodingDetect textDetect;
	TextEncodingDetect::Encoding curEncoding = textDetect.DetectEncoding(buffer, fsize);

	EncodingType encoding;
	switch (curEncoding)
	{
	case TextEncodingDetect::None: 
		wprintf(L"Binary file does not supported");
		return (ErrorCode_BadModel);
	case TextEncodingDetect::ASCII:
	case TextEncodingDetect::ANSI:
		encoding = ANSI;
		break;
	case TextEncodingDetect::UTF8_BOM:
	case TextEncodingDetect::UTF8_NOBOM: 
		encoding = UTF8;
		break;
	case TextEncodingDetect::UTF16_LE_BOM:
	case TextEncodingDetect::UTF16_LE_NOBOM:
		encoding = UTF16_LittleEndian;
		break;
	case TextEncodingDetect::UTF16_BE_BOM:
	case TextEncodingDetect::UTF16_BE_NOBOM:
		encoding = UTF16_BigEndian;
		break;
	default: 
		wprintf(L"Unknown file type");
		return (ErrorCode_BadModel);
	}

	// Free up
	delete[] buffer;
	////////////////////////////////////////////
    time_t start = time( NULL );

    CModelData modelData(encoding);

    if( !ParseArgs( argc, args, modelData ) )
    {
        return( ErrorCode_BadOption );
    }

    if( !modelData.ReadModel( wstring( args[ 1 ] )))
    {
        return( ErrorCode_BadModel );
    }

    if( !modelData.ReadRowSeedFile( modelData.RowSeedsFile ))
    {
        return( ErrorCode_BadRowSeedFile );
    }

    GcdRunner gcdRunner( modelData );

    ErrorCode err = gcdRunner.Generate();
    if( err != ErrorCode_Success )
    {
        return err;
    }

    time_t end = time( NULL );

    // if r has been provided then print out the seed
    // TODO: change to not use SWITCH_RANDOMIZE const
    if( modelData.ProvidedArguments.find( SWITCH_RANDOMIZE ) != modelData.ProvidedArguments.end() )
    {
        wcerr << L"Used seed: " << static_cast<int>( modelData.RandSeed ) << endl;
    }

    CResult result = gcdRunner.GetResult();

    if( modelData.Statistics )
    {
        modelData.PrintStatistics();
        result.PrintStatistics();
        PrintStatisticsCaption( wstring( L"Generation time" ));
        printTimeDifference( start, end );
    }
    else
    {
        result.PrintConstraintWarnings();
        result.PrintOutput( modelData );
    }

    return( ErrorCode_Success );
}

#if !defined(_MSC_VER)
//
// Gcc doesn't understand wchar_t args
// This entry point is a workaround for compiling with a non-MS compiler
//
int main
    (
    IN int   argc,
    IN char* args[]
    )
{
    // convert all args to wchar_t's
    wchar_t** wargs = new wchar_t*[ argc ];
    for ( int ii = 0; ii < argc; ++ii )
    {
        size_t len = strlen( args[ ii ] );
        wargs[ ii ] = new wchar_t[ len + 1 ];
        size_t jj;
        for( jj = 0; jj < len; ++jj )
        {
            wargs[ ii ][ jj ] = (wchar_t) args[ ii ][ jj ];
        }
        wargs[ ii ][ jj ] = L'\0';
    }

    // invoke wmain
    int ret = wmain( argc, wargs );

    // clean up
    for ( int ii = 0; ii < argc; ++ii )
    {
        delete wargs[ ii ];
    }
    delete wargs;

    return( ret );
}
#endif

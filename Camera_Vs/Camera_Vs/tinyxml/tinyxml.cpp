/*
www.sourceforge.net/projects/tinyxml
Original code (2.0 and earlier )copyright (c) 2000-2002 Lee Thomason (www.grinninglizard.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any
damages arising from the use of this software.

Permission is granted to anyone to use this software for any
purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must
not claim that you wrote the original software. If you use this
software in a product, an acknowledgment in the product documentation
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/
/*
**  ************************************************************************
**                             xml�������
** 
**
**         (c) Copyright 1992-2006, ZheJiang Dahua Technology Stock Co.Ltd.
**                            All Rights Reserved
**
**	File  Name	: tinyxml.cpp
**	Description	: ����doc��xml�ַ�����ת��
**
**	Modification	: 2006/6/10		jacko
**					add DocToString(), Printe(), SaveString()�Ⱥ���
**  ************************************************************************
*/
#include "stdafx.h"
#include <ctype.h>
#include "tinyxml.h"


#define MAX_XML_SIZE	(4 * 1024 * 4)

#define SAFE_STRCAT \
	len += (int)strlen(tempstr); \
	if ( len >= totallen ) \
	{ \
		return -1; \
	} \
	strcat(xmlstr, tempstr)

bool TiXmlBase::condenseWhiteSpace = true;

void TiXmlBase::PutString( const TIXML_STRING& str, TIXML_OSTREAM* stream )
{
	TIXML_STRING buffer;
	PutString( str, &buffer );
	(*stream) << buffer;
}

void TiXmlBase::PutString( const TIXML_STRING& str, TIXML_STRING* outString )
{
	int i=0;

	while( i<(int)str.length() )
	{
		int c = str[i];

		if (    c == '&' 
		     && i < ( (int)str.length() - 2 )
			 && str[i+1] == '#'
			 && str[i+2] == 'x' )
		{
			// Hexadecimal character reference.
			// Pass through unchanged.
			// &#xA9;	-- copyright symbol, for example.
			while ( i<(int)str.length() )
			{
				outString->append( str.c_str() + i, 1 );
				++i;
				if ( str[i] == ';' )
					break;
			}
		}
		else if ( c == '&' )
		{
			outString->append( entity[0].str, entity[0].strLength );
			++i;
		}
		else if ( c == '<' )
		{
			outString->append( entity[1].str, entity[1].strLength );
			++i;
		}
		else if ( c == '>' )
		{
			outString->append( entity[2].str, entity[2].strLength );
			++i;
		}
		else if ( c == '\"' )
		{
			outString->append( entity[3].str, entity[3].strLength );
			++i;
		}
		else if ( c == '\'' )
		{
			outString->append( entity[4].str, entity[4].strLength );
			++i;
		}
		else if ( (0 <= c && c < 32) || (c > 126 && c <= 127) )
		{
			// Easy pass at non-alpha/numeric/symbol
			// 127 is the delete key. Below 32 is symbolic.
			char buf[ 32 ];
			sprintf( buf, "&#x%02X;", (unsigned) ( c & 0xff ) );
			outString->append( buf, strlen( buf ) );
			++i;
		}
		else
		{
			char realc[2];
			realc[0] = (char) c;
			realc[1] = 0;
			outString->append( realc, 1 );
			++i;
		}
	}
}


// <-- Strange class for a bug fix. Search for STL_STRING_BUG
TiXmlBase::StringToBuffer::StringToBuffer( const TIXML_STRING& str )
{
	buffer = new char[ str.length()+1 ];
	if ( buffer )
	{
		strcpy( buffer, str.c_str() );
	}
}


TiXmlBase::StringToBuffer::~StringToBuffer()
{
	delete [] buffer;
}
// End strange bug fix. -->


TiXmlNode::TiXmlNode( NodeType _type )
{
	parent = 0;
	type = _type;
	firstChild = 0;
	lastChild = 0;
	prev = 0;
	next = 0;
	userData = 0;
}


TiXmlNode::~TiXmlNode()
{
	TiXmlNode* node = firstChild;
	TiXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}	
}


void TiXmlNode::Clear()
{
	TiXmlNode* node = firstChild;
	TiXmlNode* temp = 0;

	while ( node )
	{
		temp = node;
		node = node->next;
		delete temp;
	}	

	firstChild = 0;
	lastChild = 0;
}


TiXmlNode* TiXmlNode::LinkEndChild( TiXmlNode* node )
{
	node->parent = this;

	node->prev = lastChild;
	node->next = 0;

	if ( lastChild )
		lastChild->next = node;
	else
		firstChild = node;			// it was an empty list.

	lastChild = node;
	return node;
}


TiXmlNode* TiXmlNode::InsertEndChild( const TiXmlNode& addThis )
{
	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;

	return LinkEndChild( node );
}


TiXmlNode* TiXmlNode::InsertBeforeChild( TiXmlNode* beforeThis, const TiXmlNode& addThis )
{	
	if ( !beforeThis || beforeThis->parent != this )
		return 0;

	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->next = beforeThis;
	node->prev = beforeThis->prev;
	if ( beforeThis->prev )
	{
		beforeThis->prev->next = node;
	}
	else
	{
		assert( firstChild == beforeThis );
		firstChild = node;
	}
	beforeThis->prev = node;
	return node;
}


TiXmlNode* TiXmlNode::InsertAfterChild( TiXmlNode* afterThis, const TiXmlNode& addThis )
{
	if ( !afterThis || afterThis->parent != this )
		return 0;

	TiXmlNode* node = addThis.Clone();
	if ( !node )
		return 0;
	node->parent = this;

	node->prev = afterThis;
	node->next = afterThis->next;
	if ( afterThis->next )
	{
		afterThis->next->prev = node;
	}
	else
	{
		assert( lastChild == afterThis );
		lastChild = node;
	}
	afterThis->next = node;
	return node;
}


TiXmlNode* TiXmlNode::ReplaceChild( TiXmlNode* replaceThis, const TiXmlNode& withThis )
{
	if ( replaceThis->parent != this )
		return 0;

	TiXmlNode* node = withThis.Clone();
	if ( !node )
		return 0;

	node->next = replaceThis->next;
	node->prev = replaceThis->prev;

	if ( replaceThis->next )
		replaceThis->next->prev = node;
	else
		lastChild = node;

	if ( replaceThis->prev )
		replaceThis->prev->next = node;
	else
		firstChild = node;

	delete replaceThis;
	node->parent = this;
	return node;
}


bool TiXmlNode::RemoveChild( TiXmlNode* removeThis )
{
	if ( removeThis->parent != this )
	{	
		assert( 0 );
		return false;
	}

	if ( removeThis->next )
		removeThis->next->prev = removeThis->prev;
	else
		lastChild = removeThis->prev;

	if ( removeThis->prev )
		removeThis->prev->next = removeThis->next;
	else
		firstChild = removeThis->next;

	delete removeThis;
	return true;
}

TiXmlNode* TiXmlNode::FirstChild( const char * value ) const
{
	TiXmlNode* node;
	for ( node = firstChild; node; node = node->next )
	{
		if ( node->SValue() == TIXML_STRING( value ))
			return node;
	}
	return 0;
}

TiXmlNode* TiXmlNode::LastChild( const char * value ) const
{
	TiXmlNode* node;
	for ( node = lastChild; node; node = node->prev )
	{
		if ( node->SValue() == TIXML_STRING (value))
			return node;
	}
	return 0;
}

TiXmlNode* TiXmlNode::IterateChildren( TiXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild();
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling();
	}
}

TiXmlNode* TiXmlNode::IterateChildren( const char * val, TiXmlNode* previous ) const
{
	if ( !previous )
	{
		return FirstChild( val );
	}
	else
	{
		assert( previous->parent == this );
		return previous->NextSibling( val );
	}
}

TiXmlNode* TiXmlNode::NextSibling( const char * value ) const
{
	TiXmlNode* node;
	for ( node = next; node; node = node->next )
	{
		if ( node->SValue() == TIXML_STRING (value))
			return node;
	}
	return 0;
}


TiXmlNode* TiXmlNode::PreviousSibling( const char * value ) const
{
	TiXmlNode* node;
	for ( node = prev; node; node = node->prev )
	{
		if ( node->SValue() == TIXML_STRING (value))
			return node;
	}
	return 0;
}

void TiXmlElement::RemoveAttribute( const char * name )
{
	TiXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		attributeSet.Remove( node );
		delete node;
	}
}

TiXmlElement* TiXmlNode::FirstChildElement() const
{
	TiXmlNode* node;

	for (	node = FirstChild();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::FirstChildElement( const char * value ) const
{
	TiXmlNode* node;

	for (	node = FirstChild( value );
	node;
	node = node->NextSibling( value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}


TiXmlElement* TiXmlNode::NextSiblingElement() const
{
	TiXmlNode* node;

	for (	node = NextSibling();
	node;
	node = node->NextSibling() )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}

TiXmlElement* TiXmlNode::NextSiblingElement( const char * value ) const
{
	TiXmlNode* node;

	for (	node = NextSibling( value );
	node;
	node = node->NextSibling( value ) )
	{
		if ( node->ToElement() )
			return node->ToElement();
	}
	return 0;
}



TiXmlDocument* TiXmlNode::GetDocument() const
{
	const TiXmlNode* node;

	for( node = this; node; node = node->parent )
	{
		if ( node->ToDocument() )
			return node->ToDocument();
	}
	return 0;
}


TiXmlElement::TiXmlElement (const char * _value)
: TiXmlNode( TiXmlNode::ELEMENT )
{
	firstChild = lastChild = 0;
	value = _value;
}

TiXmlElement::~TiXmlElement()
{
	while( attributeSet.First() )
	{
		TiXmlAttribute* node = attributeSet.First();
		attributeSet.Remove( node );
		delete node;
	}
}

const char * TiXmlElement::Attribute( const char * name ) const
{
	TiXmlAttribute* node = attributeSet.Find( name );

	if ( node )
		return node->Value();

	return 0;
}


const char * TiXmlElement::Attribute( const char * name, int* i ) const
{
	const char * s = Attribute( name );
	if ( i )
	{
		if ( s )
			*i = atoi( s );
		else
			*i = 0;
	}
	return s;
}


void TiXmlElement::SetAttribute( const char * name, int val )
{	
	char buf[64];
	sprintf( buf, "%d", val );
	SetAttribute( name, buf );
}

void TiXmlElement::SetAttribute( const char * name, unsigned int val )
{	
	char buf[64];
	sprintf( buf, "%d", val );
	SetAttribute( name, buf );
}

void TiXmlElement::SetAttribute( const char * name, unsigned long val )
{	
	char buf[64];
	sprintf( buf, "%lu", val );
	SetAttribute( name, buf );
}

void TiXmlElement::SetAttribute( const char * name, TiXmlUInt64 val )
{	
	char buf[64];
	sprintf( buf, "%llu", val );
	SetAttribute( name, buf );
}


void TiXmlElement::SetAttribute( const char * name, const char * value )
{
	TiXmlAttribute* node = attributeSet.Find( name );
	if ( node )
	{
		node->SetValue( value );
		return;
	}

	TiXmlAttribute* attrib = new TiXmlAttribute( name, value );
	if ( attrib )
	{
		attributeSet.Add( attrib );
	}
	else
	{
		TiXmlDocument* document = GetDocument();
		if ( document ) document->SetError( TIXML_ERROR_OUT_OF_MEMORY );
	}
}

void TiXmlElement::Print( FILE* cfile, int depth ) const
{
	int i;
	for ( i=0; i<depth; i++ )
	{
		fprintf( cfile, "    " );
	}

	fprintf( cfile, "<%s", value.c_str() );

	TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		fprintf( cfile, " " );
		attrib->Print( cfile, depth );
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	TiXmlNode* node;
	if ( !firstChild )
	{
		fprintf( cfile, " />" );
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		fprintf( cfile, ">" );
		firstChild->Print( cfile, depth + 1 );
		fprintf( cfile, "</%s>", value.c_str() );
	}
	else
	{
		fprintf( cfile, ">" );

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				fprintf( cfile, "\n" );
			}
			node->Print( cfile, depth+1 );
		}
		fprintf( cfile, "\n" );
		for( i=0; i<depth; ++i )
		fprintf( cfile, "    " );
		fprintf( cfile, "</%s>", value.c_str() );
	}
}

/*jacko*/
//#ifdef _PUTSTRING

void TiXmlElement::Printe( char * xmlstr, int depth ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	
	int i;
	for ( i=0; i<depth; i++ )
	{
		sprintf( tempstr, "    " );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}

	sprintf( tempstr, "<%s", value.c_str() );
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

	TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		sprintf( tempstr, " " );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

		attrib->Printe( xmlstr, depth );
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	TiXmlNode* node;
	if ( !firstChild )
	{
		sprintf( tempstr, " />" );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		sprintf( tempstr, ">" );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

		firstChild->Printe( xmlstr, depth + 1 );

		sprintf( tempstr, "</%s>", value.c_str() );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	else
	{
		sprintf( tempstr, ">" );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

		for ( node = firstChild; node; node = node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				sprintf( tempstr, "\n" );
				strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
			}
			node->Printe( xmlstr, depth + 1 );
		}

		sprintf( tempstr, "\n" );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

		for( i=0; i<depth; ++i )
		{
			sprintf( tempstr, "    " );
			strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
		}
		sprintf( tempstr, "</%s>", value.c_str() );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}	
}

int TiXmlElement::Printe( char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};

	int i;
	for ( i=0; i<depth; i++ )
	{
		sprintf( tempstr, "    " );
		SAFE_STRCAT;
	}

	sprintf( tempstr, "<%s", value.c_str() );
	SAFE_STRCAT;

	TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{
		sprintf( tempstr, " " );
		SAFE_STRCAT;

		if ( attrib->Printe( xmlstr, totallen, depth, len ) < 0 )
		{
			return -2;
		}
	}

	// There are 3 different formatting approaches:
	// 1) An element without children is printed as a <foo /> node
	// 2) An element with only a text child is printed as <foo> text </foo>
	// 3) An element with children is printed on multiple lines.
	TiXmlNode* node;
	if ( !firstChild )
	{
		sprintf( tempstr, " />" );
		SAFE_STRCAT;
	}
	else if ( firstChild == lastChild && firstChild->ToText() )
	{
		sprintf( tempstr, ">" );
		SAFE_STRCAT;

		if ( firstChild->Printe( xmlstr, totallen, depth + 1, len ) < 0 )
		{
			return -2;
		}

		sprintf( tempstr, "</%s>", value.c_str() );
		SAFE_STRCAT;
	}
	else
	{
		sprintf( tempstr, ">" );
		SAFE_STRCAT;

		for ( node = firstChild; node; node = node->NextSibling() )
		{
			if ( !node->ToText() )
			{
				sprintf( tempstr, "\n" );
				SAFE_STRCAT;
			}
			if ( node->Printe( xmlstr, totallen, depth + 1, len ) < 0 )
			{
				return -2;
			}
		}

		sprintf( tempstr, "\n" );
		SAFE_STRCAT;

		for( i=0; i<depth; ++i )
		{
			sprintf( tempstr, "    " );
			SAFE_STRCAT;
		}
		sprintf( tempstr, "</%s>", value.c_str() );
		SAFE_STRCAT;
	}

	return 0;
}

//#endif	//_PUTSTRING



void TiXmlElement::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value;

	TiXmlAttribute* attrib;
	for ( attrib = attributeSet.First(); attrib; attrib = attrib->Next() )
	{	
		(*stream) << " ";
		attrib->StreamOut( stream );
	}

	// If this node has children, give it a closing tag. Else
	// make it an empty tag.
	TiXmlNode* node;
	if ( firstChild )
	{ 		
		(*stream) << ">";

		for ( node = firstChild; node; node=node->NextSibling() )
		{
			node->StreamOut( stream );
		}
		(*stream) << "</" << value << ">";
	}
	else
	{
		(*stream) << " />";
	}
}

TiXmlNode* TiXmlElement::Clone() const
{
	TiXmlElement* clone = new TiXmlElement( Value() );
	if ( !clone )
		return 0;

	CopyToClone( clone );

	// Clone the attributes, then clone the children.
	TiXmlAttribute* attribute = 0;
	for(	attribute = attributeSet.First();
	attribute;
	attribute = attribute->Next() )
	{
		clone->SetAttribute( attribute->Name(), attribute->Value() );
	}

	TiXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		clone->LinkEndChild( node->Clone() );
	}
	return clone;
}


TiXmlDocument::TiXmlDocument() : TiXmlNode( TiXmlNode::DOCUMENT )
{
	error = false;
	//	ignoreWhiteSpace = true;
}

TiXmlDocument::TiXmlDocument( const char * documentName ) : TiXmlNode( TiXmlNode::DOCUMENT )
{
	//	ignoreWhiteSpace = true;
	value = documentName;
	error = false;
}

bool TiXmlDocument::LoadFile()
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && LoadFile( buf.buffer ) )
		return true;

	return false;
}

/*jacko*/
//bool TiXmlDocument::SaveFile(char * xmlstr) 
//{
//	// The old c stuff lives on...
//	//int readlen = 0;
////	int pos = 0;
//	//char fName[255];
//	//strcpy(fName, xmlstr);
//	//FILE* fp = fopen( fName, "w" );
//	FILE* fp = fopen( fName, "w" );
//	if ( fp )
//	{
//		Print( fp, 0 );
//		fclose( fp );
//		//if ( fp = fopen(fName, "r") )
//		//{
//		//    readlen = fread( xmlstr, MAX_XML_SIZE, 1, fp );
//		//	fclose(fp);
//
//		//}
//		return true;
//	}
//	return false;
//}


bool TiXmlDocument::SaveFile() const
{
	// See STL_STRING_BUG below.
	StringToBuffer buf( value );

	if ( buf.buffer && SaveFile( buf.buffer ) )
		return true;

	return false;
}


bool TiXmlDocument::LoadFile( const char* filename )
{
	// Delete the existing data:
	Clear();

	// There was a really terrifying little bug here. The code:
	//		value = filename
	// in the STL case, cause the assignment method of the std::string to
	// be called. What is strange, is that the std::string had the same
	// address as it's c_str() method, and so bad things happen. Looks
	// like a bug in the Microsoft STL implementation.
	// See STL_STRING_BUG above.
	// Fixed with the StringToBuffer class.
	value = filename;

	FILE* file = fopen( value.c_str (), "r" );

	if ( file )
	{
		// Get the file size, so we can pre-allocate the string. HUGE speed impact.
		long length = 0;
		fseek( file, 0, SEEK_END );
		length = ftell( file );
		fseek( file, 0, SEEK_SET );

		// Strange case, but good to handle up front.
		if ( length == 0 )
		{
			fclose( file );
			return false;
		}

		// If we have a file, assume it is all one big XML file, and read it in.
		// The document parser may decide the document ends sooner than the entire file, however.
		TIXML_STRING data;
		data.reserve( length );

		const int BUF_SIZE = 2048;
		char buf[BUF_SIZE];

		while( fgets( buf, BUF_SIZE, file ) )
		{
			data += buf;
		}
		fclose( file );

		Parse( data.c_str() );
		if (  Error() )
            return false;
        else
			return true;
	}
	SetError( TIXML_ERROR_OPENING_FILE );
	return false;
}

bool TiXmlDocument::SaveFile( const char * filename ) const
{
	// The old c stuff lives on...
	FILE* fp = fopen( filename, "w" );
	if ( fp )
	{
		Print( fp, 0 );
		fclose( fp );
		return true;
	}
	return false;
}


TiXmlNode* TiXmlDocument::Clone() const
{
	TiXmlDocument* clone = new TiXmlDocument();
	if ( !clone )
		return 0;

	CopyToClone( clone );
	clone->error = error;
	clone->errorDesc = errorDesc.c_str ();

	TiXmlNode* node = 0;
	for ( node = firstChild; node; node = node->NextSibling() )
	{
		clone->LinkEndChild( node->Clone() );
	}
	return clone;
}


void TiXmlDocument::Print( FILE* cfile, int depth ) const
{
	TiXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->Print( cfile, depth );
		fprintf( cfile, "\n" );
	}
}

/*jacko*/
//#ifdef _SAVESTRING

bool TiXmlDocument::DocToString(char * xmlstr) 
{
	*xmlstr = 0;
	if ( SaveString( xmlstr ) )
		return true;

	return false;
}

bool TiXmlDocument::DocToString(char *xmlstr, int totallen, int &len)
{
	*xmlstr = 0;
	if ( Printe(xmlstr, totallen, 0, len ) < 0 )
	{
		return false;
	}

	return true;
}

bool TiXmlDocument::SaveString( char * xmlstr ) 
{
	Printe( xmlstr, 0 );
	
	return true;
}


void TiXmlDocument::Printe( char * xmlstr, int depth ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TiXmlNode* node = NULL;
	for ( node = FirstChild(); node; node = node->NextSibling() )
	{
//#ifdef _PUTSTRING
		node->Printe( xmlstr, depth );
//#endif
		sprintf( tempstr, "\n" );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
}

int TiXmlDocument::Printe( char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TiXmlNode* node = NULL;
	for ( node = FirstChild(); node; node = node->NextSibling() )
	{
		//#ifdef _PUTSTRING
		if ( node->Printe( xmlstr, totallen, depth, len ) < 0 )
		{
			return -2;
		}
		//#endif
		sprintf( tempstr, "\n" );
		SAFE_STRCAT;
	}

	return 0;
}

//#endif	//_PUTSTRING


void TiXmlDocument::StreamOut( TIXML_OSTREAM * out ) const
{
	TiXmlNode* node;
	for ( node=FirstChild(); node; node=node->NextSibling() )
	{
		node->StreamOut( out );

		// Special rule for streams: stop after the root element.
		// The stream in code will only read one element, so don't
		// write more than one.
		if ( node->ToElement() )
			break;
	}
}

TiXmlAttribute* TiXmlAttribute::Next() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( next->value.empty() && next->name.empty() )
		return 0;
	return next;
}


TiXmlAttribute* TiXmlAttribute::Previous() const
{
	// We are using knowledge of the sentinel. The sentinel
	// have a value or name.
	if ( prev->value.empty() && prev->name.empty() )
		return 0;
	return prev;
}


void TiXmlAttribute::Print( FILE* cfile, int /*depth*/ ) const
{
	TIXML_STRING n, v;

	PutString( Name(), &n );
	PutString( Value(), &v );

	if (value.find ('\"') == TIXML_STRING::npos)
		fprintf (cfile, "%s=\"%s\"", n.c_str(), v.c_str() );
		//fprintf (cfile, "%s=\"%s\"", name.c_str(), value.c_str() );
	else
		fprintf (cfile, "%s='%s'", n.c_str(), v.c_str() );
		//fprintf (cfile, "%s=\"%s\"", name.c_str(), value.c_str() );
}

/*jacko*/
//#ifdef _PUTSTRING

void TiXmlAttribute::Printe( char * xmlstr, int depth ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TIXML_STRING n, v;

	PutString( Name(), &n );
	PutString( Value(), &v );

	if (value.find ('\"') == TIXML_STRING::npos)
	{
		sprintf (tempstr, "%s=\"%s\"", n.c_str(), v.c_str() );
		//sprintf (tempstr, "%s=\"%s\"", name.c_str(), value.c_str() );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	else
	{
		sprintf (tempstr, "%s='%s'", n.c_str(), v.c_str() );
		//sprintf (tempstr, "%s=\"%s\"", name.c_str(), value.c_str() );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
}

int TiXmlAttribute::Printe( char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TIXML_STRING n, v;

	PutString( Name(), &n );
	PutString( Value(), &v );

	//�ж�û�����壬'\"'�Ѿ�����ת��, gaowei 09-07-14
	//if (value.find ('\"') == TIXML_STRING::npos)
	{
		sprintf (tempstr, "%s=\"%s\"", n.c_str(), v.c_str() );
		//sprintf (tempstr, "%s=\"%s\"", name.c_str(), value.c_str() );
		SAFE_STRCAT;
	}
	//else
	//{
	//	sprintf (tempstr, "%s='%s'", n.c_str(), v.c_str() );
	//	//sprintf (tempstr, "%s=\"%s\"", name.c_str(), value.c_str() );
	//	SAFE_STRCAT;
	//}

	return 0;
}

//#endif	//_PUTSTRING


void TiXmlAttribute::StreamOut( TIXML_OSTREAM * stream ) const
{
	if (value.find( '\"' ) != TIXML_STRING::npos)
	{
		PutString( name, stream );
		(*stream) << "=" << "'";
		PutString( value, stream );
		(*stream) << "'";
	}
	else
	{
		PutString( name, stream );
		(*stream) << "=" << "\"";
		PutString( value, stream );
		(*stream) << "\"";
	}
}

void TiXmlAttribute::SetIntValue( int value )
{
	char buf [64];
	sprintf (buf, "%d", value);
	SetValue (buf);
}

void TiXmlAttribute::SetDoubleValue( double value )
{
	char buf [64];
	sprintf (buf, "%lf", value);
	SetValue (buf);
}

const int TiXmlAttribute::IntValue() const
{
	return atoi (value.c_str ());
}

const double  TiXmlAttribute::DoubleValue() const
{
	return atof (value.c_str ());
}

void TiXmlComment::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
	{
		fputs( "    ", cfile );
	}
	fprintf( cfile, "<!--%s-->", value.c_str() );
}

void TiXmlComment::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<!--";
	PutString( value, stream );
	(*stream) << "-->";
}

TiXmlNode* TiXmlComment::Clone() const
{
	TiXmlComment* clone = new TiXmlComment();

	if ( !clone )
		return 0;

	CopyToClone( clone );
	return clone;
}


void TiXmlText::Print( FILE* cfile, int /*depth*/ ) const
{
	TIXML_STRING buffer;
	PutString( value, &buffer );
	fprintf( cfile, "%s", buffer.c_str() );
	//fprintf( cfile, "%s", value.c_str() );
}

/*jacko*/
//#ifdef _PUTSTRING

void TiXmlComment::Printe(  char * xmlstr, int depth  ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	for ( int i = 0; i < depth; i++ )
	{
		sprintf( tempstr, "    " );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

	}
	sprintf( tempstr, "<!--%s-->", value.c_str() );
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
}

int TiXmlComment::Printe(  char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	for ( int i = 0; i < depth; i++ )
	{
		sprintf( tempstr, "    " );
		SAFE_STRCAT;
	}
	sprintf( tempstr, "<!--%s-->", value.c_str() );
	SAFE_STRCAT;
	return 0;
}

void TiXmlText::Printe( char * xmlstr, int /*depth*/ ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TIXML_STRING buffer;
	PutString( value, &buffer );

	sprintf( tempstr, "%s", buffer.c_str() );
	//sprintf( tempstr, "%s", value.c_str() );
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr));
}

int TiXmlText::Printe( char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	TIXML_STRING buffer;
	PutString( value, &buffer );

	sprintf( tempstr, "%s", buffer.c_str() );
	//sprintf( tempstr, "%s", value.c_str() );
	SAFE_STRCAT;
	return 0;
}

//#endif	//_PUTSTRING


void TiXmlText::StreamOut( TIXML_OSTREAM * stream ) const
{
	PutString( value, stream );
}


TiXmlNode* TiXmlText::Clone() const
{	
	TiXmlText* clone = 0;
	clone = new TiXmlText( "" );

	if ( !clone )
		return 0;

	CopyToClone( clone );
	return clone;
}


TiXmlDeclaration::TiXmlDeclaration( const char * _version,
	const char * _encoding,
	const char * _standalone )
: TiXmlNode( TiXmlNode::DECLARATION )
{
	version = _version;
	encoding = _encoding;
	standalone = _standalone;
}


void TiXmlDeclaration::Print( FILE* cfile, int /*depth*/ ) const
{
	fprintf (cfile, "<?xml ");

	if ( !version.empty() )
		fprintf (cfile, "version=\"%s\" ", version.c_str ());
	if ( !encoding.empty() )
		fprintf (cfile, "encoding=\"%s\" ", encoding.c_str ());
	if ( !standalone.empty() )
		fprintf (cfile, "standalone=\"%s\" ", standalone.c_str ());
	fprintf (cfile, "?>");
}

/*jacko*/
//#ifdef _SAVESTRING

void TiXmlDeclaration::Printe( char * xmlstr, int depth ) 
{
	char tempstr[MAX_XML_SIZE] = {0};

	sprintf (tempstr, "<?xml ");
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 

	if ( !version.empty() )
	{
		sprintf (tempstr, "version=\"%s\" ", version.c_str ());
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	if ( !encoding.empty() )
	{
		sprintf (tempstr, "encoding=\"%s\" ", encoding.c_str ());
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	if ( !standalone.empty() )
	{
		sprintf (tempstr, "standalone=\"%s\" ", standalone.c_str ());
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}

	sprintf (tempstr, "?>");
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
}

int TiXmlDeclaration::Printe( char * xmlstr, int totallen, int depth, int& len ) 
{
	char tempstr[MAX_XML_SIZE] = {0};

	sprintf (tempstr, "<?xml ");
	SAFE_STRCAT;

	if ( !version.empty() )
	{
		sprintf (tempstr, "version=\"%s\" ", version.c_str ());
		SAFE_STRCAT;
	}
	if ( !encoding.empty() )
	{
		sprintf (tempstr, "encoding=\"%s\" ", encoding.c_str ());
		SAFE_STRCAT;
	}
	if ( !standalone.empty() )
	{
		sprintf (tempstr, "standalone=\"%s\" ", standalone.c_str ());
		SAFE_STRCAT;
	}

	sprintf (tempstr, "?>");
	SAFE_STRCAT;
	return 0;
}

void TiXmlUnknown::Printe(char * xmlstr, int depth) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	for ( int i = 0; i < depth; i++ )
	{
		sprintf( tempstr, "    " );
		strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
	}
	sprintf( tempstr, "%s", value.c_str() );
	strcat(xmlstr, tempstr); //printf("String = %s, string len = %d\n", tempstr, strlen(tempstr)); 
}

int TiXmlUnknown::Printe(char * xmlstr, int totallen, int depth, int& len) 
{
	char tempstr[MAX_XML_SIZE] = {0};
	for ( int i = 0; i < depth; i++ )
	{
		sprintf( tempstr, "    " );
		SAFE_STRCAT;
	}
	sprintf( tempstr, "%s", value.c_str() );
	SAFE_STRCAT;
	return 0;
}

//#endif	//_PUTSTRING


void TiXmlDeclaration::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<?xml ";

	if ( !version.empty() )
	{
		(*stream) << "version=\"";
		PutString( version, stream );
		(*stream) << "\" ";
	}
	if ( !encoding.empty() )
	{
		(*stream) << "encoding=\"";
		PutString( encoding, stream );
		(*stream ) << "\" ";
	}
	if ( !standalone.empty() )
	{
		(*stream) << "standalone=\"";
		PutString( standalone, stream );
		(*stream) << "\" ";
	}
	(*stream) << "?>";
}

TiXmlNode* TiXmlDeclaration::Clone() const
{	
	TiXmlDeclaration* clone = new TiXmlDeclaration();

	if ( !clone )
		return 0;

	CopyToClone( clone );
	clone->version = version;
	clone->encoding = encoding;
	clone->standalone = standalone;
	return clone;
}


void TiXmlUnknown::Print( FILE* cfile, int depth ) const
{
	for ( int i=0; i<depth; i++ )
		fprintf( cfile, "    " );
	fprintf( cfile, "%s", value.c_str() );
}

void TiXmlUnknown::StreamOut( TIXML_OSTREAM * stream ) const
{
	(*stream) << "<" << value << ">";		// Don't use entities hear! It is unknown.
}

TiXmlNode* TiXmlUnknown::Clone() const
{
	TiXmlUnknown* clone = new TiXmlUnknown();

	if ( !clone )
		return 0;

	CopyToClone( clone );
	return clone;
}


TiXmlAttributeSet::TiXmlAttributeSet()
{
	sentinel.next = &sentinel;
	sentinel.prev = &sentinel;
}


TiXmlAttributeSet::~TiXmlAttributeSet()
{
	assert( sentinel.next == &sentinel );
	assert( sentinel.prev == &sentinel );
}


void TiXmlAttributeSet::Add( TiXmlAttribute* addMe )
{
	assert( !Find( addMe->Name() ) );	// Shouldn't be multiply adding to the set.

	addMe->next = &sentinel;
	addMe->prev = sentinel.prev;

	sentinel.prev->next = addMe;
	sentinel.prev      = addMe;
}

void TiXmlAttributeSet::Remove( TiXmlAttribute* removeMe )
{
	TiXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node == removeMe )
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			node->next = 0;
			node->prev = 0;
			return;
		}
	}
	assert( 0 );		// we tried to remove a non-linked attribute.
}

TiXmlAttribute*	TiXmlAttributeSet::Find( const char * name ) const
{
	TiXmlAttribute* node;

	for( node = sentinel.next; node != &sentinel; node = node->next )
	{
		if ( node->name == name )
			return node;
	}
	return 0;
}


#ifdef TIXML_USE_STL	
TIXML_ISTREAM & operator >> (TIXML_ISTREAM & in, TiXmlNode & base)
{
	TIXML_STRING tag;
	tag.reserve( 8 * 1000 );
	base.StreamIn( &in, &tag );

	base.Parse( tag.c_str() );
	return in;
}
#endif


TIXML_OSTREAM & operator<< (TIXML_OSTREAM & out, const TiXmlNode & base)
{
	base.StreamOut (& out);
	return out;
}

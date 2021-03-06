/*
 * VOUW - Spatial, compression-based pattern mining on matrices
 *
 * Micky Faas <micky@edukitty.org>
 * (C) 2018, Leiden Institute for Advanced Computer Science
 */

#pragma once
#include "vouw.h"
#include <cinttypes>

VOUW_NAMESPACE_BEGIN

#define VOUW_UNODE32_FLAGGED (1U << 31)

class Coord2D {
    public:
        typedef struct {
            int row,col;
        } PairT;

        PairT m;

        Coord2D( int row, int col, int rowLength =0 ) : m( {row,col} ), m_rowLength(rowLength) {}
        Coord2D() : m( {0,0} ) {}

        void setRow( int row) { m.row =row; }
        int row() const { return m.row; }

        void setCol( int col) { m.col =col; }
        int col() const { return m.col; }

        bool isZero() { return m.row == 0 && m.col == 0; }

        void setRowLength( int rowLength ) { m_rowLength = rowLength; } 
        int rowLength() const { return m_rowLength; }

        virtual int position() const;

    private:
        int m_rowLength;

};

bool operator==( const Coord2D&, const Coord2D& );
bool operator!=( const Coord2D&, const Coord2D& );
bool operator<=( const Coord2D&, const Coord2D& );
bool operator<( const Coord2D&, const Coord2D& );
bool operator>=( const Coord2D&, const Coord2D& );
bool operator>( const Coord2D&, const Coord2D& );

class MassFunction;

class Matrix2D {
    public:
        typedef uint32_t ElementT;
        Matrix2D( unsigned int width, unsigned int height, unsigned int base );
        Matrix2D( const Matrix2D& );
        ~Matrix2D();

        Coord2D makeCoord( int row, int col );

        unsigned int width() const { return m_width; }
        unsigned int height() const { return m_height; }
        unsigned int count() const { return m_width * m_height; }
        unsigned int base() const { return m_base; }

        void clear();

        ElementT* data();
        const ElementT* data() const;
        ElementT* rowPtr( unsigned int row );
        const ElementT* rowPtr( unsigned int row ) const;

        //ElementT& value( Coord2D );
        ElementT value( Coord2D ) const;
        void setValue( Coord2D, const ElementT&);

        void setFlagged( const Coord2D&, bool );
        bool isFlagged( const Coord2D& ) const;
        void unflagAll();

        bool checkBounds( const Coord2D& ) const;

        const MassFunction& distribution( bool force_regenerate =false );

        bool operator==( const Matrix2D& );

    private:
        unsigned int m_width, m_height, m_base;
        ElementT* m_buffer;
        MassFunction* m_massfunc;
};

VOUW_NAMESPACE_END


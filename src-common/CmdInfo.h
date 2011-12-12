// CmdInfo.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2010 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//


#ifndef INCLUDE_CMDINFO_H
#define INCLUDE_CMDINFO_H

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#include <limits>
#include <agg_basics.h>
#include "agg_path_storage.h"
#include <deque>
#include <stdint.h>

namespace AST {
    class ASTpathCommand;
    class ASTcompiledPath;
    
    struct CommandInfo {
#if defined(__ppc__) || defined(__powerpc__)
        typedef uint32_t    UIDtype;
#else
        typedef uint64_t    UIDtype;
#endif
        int                 mFlags;
        double              mMiterLimit;
        double              mStrokeWidth;
        unsigned            mIndex;
        agg::path_storage*  mPath;
        UIDtype             mPathUID;
        
        static const CommandInfo
                            Default;
        
        CommandInfo() 
        : mFlags(0), mMiterLimit(4.0), mStrokeWidth(0.1), mIndex(0), mPath(NULL), 
        mPathUID(std::numeric_limits<UIDtype>::max()) {};
        CommandInfo(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c = NULL);
        void tryInit(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c = NULL);
    private:
        CommandInfo(unsigned i, agg::path_storage* p);
        void init(unsigned i, ASTcompiledPath* path, double w, const ASTpathCommand* c = NULL);
    };

    typedef std::deque<CommandInfo> InfoCache;
}

#endif //INCLUDE_CMDINFO_H
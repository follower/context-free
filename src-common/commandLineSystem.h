// commandLineSystem.h
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2013 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#ifndef INCLUDE_COMMANDLINE_SYSTEM
#define INCLUDE_COMMANDLINE_SYSTEM

#include "cfdg.h"
#include <iosfwd>
#include <string>
#include <memory>
#include <map>

#ifdef _WIN32
#include "Win32System.h"
#else
#include "posixSystem.h"
#endif

#ifdef _WIN32
class CommandLineSystem : public Win32System
#else
class CommandLineSystem : public PosixSystem
#endif
{
protected:
    bool mQuiet;
    bool mNeedEndl;
    bool mErrorMode;
    std::unique_ptr<std::string> mInputBuffer;
    virtual const char* maybeLF();
public:
    CommandLineSystem(bool q = false) : mQuiet(q), mNeedEndl(false),
        mErrorMode(false) { };
    ~CommandLineSystem() override = default;
    void message(const char* fmt, ...) override;
    void syntaxError(const CfdgError& err) override;
    bool error(bool errorOccurred = true) override;
    
    std::istream* openFileForRead(const std::string& path) override;
    
    void stats(const Stats&) override;
    void orphan() override {};
private:
    static const std::map<std::string, const char*> ExamplesMap;
};

#endif // INCLUDE_COMMANDLINE_SYSTEM

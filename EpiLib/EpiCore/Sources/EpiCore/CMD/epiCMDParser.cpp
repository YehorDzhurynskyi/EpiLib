#include "EpiCore/CMD/epiCMDParser.h"

EPI_NAMESPACE_BEGIN()

epiCMDParser epiCMDParser::Parse(epiS32 argc, const epiChar* const* argv)
{
    epiCMDParser parser;
    parser.m_Argc = argc;
    parser.m_Argv = argv;
    parser.m_Index = 0;
    parser.m_Cursor = nullptr;

    return parser;
}

epiBool epiCMDParser::HasNext() const
{
    return m_Index < m_Argc && m_Argv;
}

void epiCMDParser::Next()
{
    epiAssert(HasNext());
    do
    {
        m_Cursor = m_Argv[m_Index++];
    } while (*m_Cursor == '\0' && HasNext());
}

const epiChar* epiCMDParser::Curr() const
{
    return m_Argv[m_Index - 1];
}

epiBool epiCMDParser::Match(const epiChar* name) const
{
    const epiSize_t len = strlen(name);
    if (0 != strncmp(m_Cursor, name, len))
    {
        return false;
    }

    if (m_Cursor[len] != '\0' && m_Cursor[len - 1] != '=')
    {
        // NOTE: to prevent similar suffixes matches
        return false;
    }

    return true;
}

epiBool epiCMDParser::Flag(const epiChar* name, epiBool& to)
{
    return Flag(name, to, true);
}

epiBool epiCMDParser::FlagCB(const epiChar* name, std::function<void(void)> callback)
{
    if (!Match(name))
    {
        return false;
    }

    callback();

    return true;
}

EPI_NAMESPACE_END()

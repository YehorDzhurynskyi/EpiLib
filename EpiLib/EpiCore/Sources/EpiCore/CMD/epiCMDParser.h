#pragma once

EPI_NAMESPACE_BEGIN()

class epiCMDParser
{
public:
    static epiCMDParser Parse(epiS32 argc, const epiChar* const* argv);

protected:
    epiCMDParser() = default;

public:
    epiBool HasNext() const;
    void Next();
    const epiChar* Curr() const;

    epiBool Flag(const epiChar* name, epiBool& to);

    template<typename T, typename _T = std::decay_t<T>>
    epiBool Flag(const epiChar* name, T& to, _T value);

    epiBool FlagCB(const epiChar* name, std::function<void(void)> callback);

    template<typename T, typename _T = std::decay_t<T>>
    epiBool Arg(const epiChar* name, T& to);

    template<typename T, typename _T = std::decay_t<T>>
    epiBool ArgCB(const epiChar* name, std::function<void(T)> callback);

protected:
    epiBool Match(const epiChar* name) const;

protected:
    epiS32 m_Argc;
    const epiChar* const* m_Argv;
    epiS32 m_Index;
    const epiChar* m_Cursor;
};

template<typename T, typename _T>
epiBool epiCMDParser::Flag(const epiChar* name, T& to, _T value)
{
    if (!Match(name))
    {
        return false;
    }

    to = value;

    return true;
}

template<typename T, typename _T>
epiBool epiCMDParser::Arg(const epiChar* name, T& to)
{
    static_assert(!std::is_same_v<_T, epiBool>, "Use `epiCMDParser.flag()` function for boolean!");

    if (!Match(name))
    {
        return false;
    }

    const epiSize_t namelen = strlen(name);
    epiAssert(namelen != 0);

    if (m_Cursor[namelen - 1] != '=')
    {
        epiLogWarn("epiCMDParser: CMD argument should be followed by `=`");
        return false;
    }

    m_Cursor += namelen;

    if constexpr (std::is_same_v<const epiChar*, _T> || std::is_same_v<epiString, _T> || std::is_same_v<std::string, _T>)
    {
        to = m_Cursor;
    }
    else if constexpr (std::is_same_v<epiChar, _T>)
    {
        to = static_cast<_T>(*m_Cursor);
    }
    else if constexpr (std::is_integral_v<_T> || std::is_enum_v<_T>)
    {
        to = static_cast<_T>(std::stoi(m_Cursor));
    }
    else if constexpr (std::is_floating_point_v<_T>)
    {
        to = static_cast<_T>(std::stof(m_Cursor));
    }
    else
    {
        epiLogError("epiCMDParser: Can't parse provided cmd argument=`{}`! Unknown format!", name);
        return false;
    }

    return true;
}

template<typename T, typename _T>
epiBool epiCMDParser::ArgCB(const epiChar* name, std::function<void(T)> callback)
{
    static_assert(!std::is_same_v<_T, epiBool>, "Use `epiCMDParser.flag()` function for boolean!");

    _T value{};

    if (!Arg(name, value))
    {
        return false;
    }

    callback(value);

    return true;
}

EPI_NAMESPACE_END()

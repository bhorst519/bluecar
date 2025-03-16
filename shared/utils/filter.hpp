#ifndef FILTER_UTIL_HPP
#define FILTER_UTIL_HPP

/***************************************************************************************************
*                                         I N C L U D E S                                          *
***************************************************************************************************/
#include "util.h"

/***************************************************************************************************
*                          P U B L I C   I N L I N E   F U N C T I O N S                           *
***************************************************************************************************/
namespace Filter
{

template<typename T, typename FC, typename FD>
inline void RunIfValid(const FC& coeffs, FD& data, const T& input, const bool& inputValid, bool& valid)
{
    if ((!valid) && inputValid)
    {
        // Newly-valid data. Set state to input
        data.SetState(input);
    }
    else if (inputValid)
    {
        // Continued-valud data. Run filter
        data.Run(input, coeffs);
    }
    else
    {
        // Do nothing
    }

    valid = inputValid;
}

/***************************************************************************************************
*                                         T Y P E D E F S                                          *
***************************************************************************************************/
//--------------------------------------------------------------------------------------------------
// Top-level objects
//--------------------------------------------------------------------------------------------------
// T = input/return type
// FC = filter coefficient type
// FD = filter data type
template<typename T, typename FC, typename FD>
struct FiltCore
{
    private:
        FC m_coeffs;
        FD m_data;
        bool m_valid;

    public:
        FiltCore() =default;

        constexpr FiltCore(
                const FC& coeffs
            ) :
                m_coeffs(coeffs),
                m_data(),
                m_valid()
        {}

        constexpr FiltCore(
                const FC& coeffs,
                const FD& data,
                const bool& valid
            ) :
                m_coeffs(coeffs),
                m_data(data),
                m_valid(valid)
        {}

        T GetOutput(void) const { return m_data.GetOutput(); }
        void SetState(const T state) { m_data.SetState(state); }
        void Run(const T input) { m_data.Run(input); }
        void RunIfValid(const T input, const bool inputValid)
        {
            Filter::RunIfValid(m_coeffs, m_data, input, inputValid, m_valid);
        }
        T RunIfValidAndGetOutput(const T input, const bool inputValid)
        {
            RunIfValid(input, inputValid);
            return GetOutput();
        }
};

// F = filter type, with types:
//      DataType = T = input/return type
//      Coeff_S = FC = filter coefficient type
//      Data_S = FD = filter data type
template<typename F, size_t N>
struct Arr
{
    private:
        using T = F::DataType;
        using FC = F::Coeff_S;
        using FD = F::Data_S;
        using Core = F::Core;

        FC m_coeffs;
        FD m_data[N];
        bool m_valid[N];

    public:
        Arr() =default;

        constexpr Arr(
                const FC& coeffs
            ) :
                m_coeffs(coeffs),
                m_data(),
                m_valid()
        {}

        constexpr size_t Size(void) const { return N; }
        Core operator[](const size_t idx) { return {m_coeffs, m_data[idx], m_valid[idx]}; }

        T GetOutput(const size_t idx) const { return m_data[idx].GetOutput(); }
        void SetState(const size_t idx, const T state) { m_data[idx].SetState(state); }
        void Run(const size_t idx, const T input) { m_data[idx].Run(input); }
        void RunIfValid(const size_t idx, const T input, const bool inputValid)
        {
            Filter::RunIfValid(m_coeffs, m_data[idx], input, inputValid, m_valid[idx]);
        }
        T RunIfValidAndGetOutput(const size_t idx, const T input, const bool inputValid)
        {
            RunIfValid(idx, input, inputValid);
            return GetOutput(idx);
        }
};

//--------------------------------------------------------------------------------------------------
// Underlying filter data implementations
//--------------------------------------------------------------------------------------------------
template<typename T, typename K>
struct Lpf1st
{
    struct Coeff_S
    {
        K A; // Coefficient for delayed output
        K B; // Coefficient for input
    };

    struct Data_S
    {
        T m_output;

        T GetOutput(void) const { return m_output; }
        void SetState(const T state) { m_output = state; }
        void Run(const T& input, const Coeff_S& coeff)
        {
            const T newOutput = (  (coeff.A * m_output)
                                 + (coeff.B * input) );
            m_output = newOutput;
        }
    };

    using DataType = T;
    using Core = FiltCore<T, Coeff_S, Data_S>;

    // A = (tc)/(tc+Ts)
    // B = (Ts)/(tc+Ts),  where:
    //   tc = filter time constant = 1/(2*pi*fc)
    //   Ts = sampling time (sec) = (1/fs)
    //   fc = cutoff frequency (Hz)
    //   fs = sampling frequency (Hz)
    static constexpr Coeff_S ComputeCoeffs(const K timeConstant, const K samplingPeriod)
    {
        return Coeff_S{
            .A = (timeConstant) / (timeConstant + samplingPeriod),
            .B = (samplingPeriod) / (timeConstant + samplingPeriod),
        };
    }
};

} // namespace Filter

#endif // FILTER_UTIL_HPP

#pragma once


namespace Celeste
{
  namespace Reflection
  {
    //------------------------------------------------------------------------------------------------
    template <typename TClass, typename TMember>
    constexpr size_t getMemberOffset(TMember TClass::* member)
    {
      return (size_t)&(((TClass*)0)->*member) - (size_t)(((TClass*)0));
    }

    //------------------------------------------------------------------------------------------------
    template <typename TClass, typename TMember>
    TMember* getMember(TClass* classPtr, TMember TClass::* member)
    {
      size_t offset = getMemberOffset(member);
      return reinterpret_cast<TMember*>((size_t)classPtr + offset);
    }

    //------------------------------------------------------------------------------------------------
    template <typename TClass, typename TMember>
    void setMember(TClass* classPtr, TMember TClass::* member, TMember value)
    {
      *getMember<TClass, TMember>(classPtr, member) = value;
    }
  }
}
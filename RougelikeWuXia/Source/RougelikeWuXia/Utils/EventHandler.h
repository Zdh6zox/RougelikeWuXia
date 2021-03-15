// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UEventBase;
class IEventHandler
{
public:
    virtual void Call(UEventBase* event) = 0;
};

template<class TARGET_TYPE, typename EVENT_TYPE>
class ROUGELIKEWUXIA_API FEventCallback : public IEventHandler
{
public:
    typedef void(TARGET_TYPE::*CallbackPtr)(EVENT_TYPE&);

    void Init(TARGET_TYPE* target, CallbackPtr callbackFunc)
    {
        m_Target = target;
        m_Callback = callbackFunc;
    }

    EVENT_TYPE* CastEvent(UEventBase* event)
    {
        return Cast<EVENT_TYPE>(event);
    }

    virtual void Call(UEventBase* event)
    {
        check(m_Target != nullptr && m_Callback != nullptr);

    }

private:
    TARGET_TYPE* m_Target;
    CallbackPtr m_Callback;
};

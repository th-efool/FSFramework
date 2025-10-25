// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Misc/MessageDialog.h"
#include "Editor.h"
#include "CoreMinimal.h"


// Define one log category per severity level
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Debug, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Info, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Warn, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Error, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Fatal, Log, All);


class ErrorHandler
{
public:
	ErrorHandler();
	~ErrorHandler();
};



enum class FLoggerLevel : uint8
{
	Debug,
	Info,
	Warn,
	Error,
	Fatal
};

class FLogger
{
	public:
	static FLogger& Get()
	{
		static FLogger Instance;
		return Instance;
	}

	static inline bool bCrashOnFatal = true; // configurable switch
	
	template<typename T>
	static T Handle(
		const T& value,
		FLoggerLevel level,
		const char* expr,
		const char* file,
		int line)
	{
		
		if (IsInvalidValue(value))
		{
			LogWithLevel(level, FString::Printf(
				TEXT("[%s:%d] Invalid expression: %s"),
				ANSI_TO_TCHAR(FileNameFromPath(file)),
				line,
				ANSI_TO_TCHAR(expr)));
		}
		return value;
	}
	
	template<typename T>
	T HandleOr(const T& value, const T& fallback, FLoggerLevel level,
			   const char* expr, const char* file, int line)
	{
		if (IsInvalidValue(value))
		{
			LogWithLevel(level, FString::Printf(
				TEXT("[%s:%d] Invalid expression: %s"),
				ANSI_TO_TCHAR(FileNameFromPath(file)),
				line,
				ANSI_TO_TCHAR(expr)));
			return fallback;
		}
		return value;
	}

	template<typename T>
	static T HandleMsg(
		const T& value,
		FLoggerLevel level,
		const FString& customMsg,
		const char* file,
		int line)
	{
		if (IsInvalidValue(value))
		{
			LogWithLevel(level, FString::Printf(
				TEXT("[%s:%d] %s"),
				ANSI_TO_TCHAR(FileNameFromPath(file)),
				line,
				*customMsg));
		}
		return value;
	}

	static void PrintScreen(const FString& Text)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, Text);
			UE_LOG(LogTemp, Display, TEXT("%s"), *Text);
		}
	}

	
	static void ShowPopup(const FString& Message)
	{
		#if WITH_EDITOR
		if (GIsEditor)
		{
			FText Title = FText::FromString(TEXT("FS Framework Ensure"));
			FText Msg = FText::FromString(Message);
			FMessageDialog::Open(EAppMsgType::Ok, Msg, Title);

			if (GEditor && GEditor->IsPlayingSessionInEditor())
			{
				GEditor->RequestEndPlayMap();
			}
		}
		#endif
	}
private:
	
	static void LogWithLevel(FLoggerLevel level, const FString& msg)
	{
		switch (level)
		{
		case FLoggerLevel::Debug:
			UE_LOG(FS_Log_Debug, Log, TEXT("%s"), *msg);break;
		case FLoggerLevel::Info:
			UE_LOG(FS_Log_Info, Log, TEXT("%s"), *msg); break;
		case FLoggerLevel::Warn:
			UE_LOG(FS_Log_Warn, Warning, TEXT("%s"), *msg); break;
		case FLoggerLevel::Error:
			UE_LOG(FS_Log_Error, Error, TEXT("%s"), *msg); break;
		case FLoggerLevel::Fatal:
			UE_LOG(FS_Log_Fatal, Fatal, TEXT("%s"), *msg); 
			if (bCrashOnFatal)
			{checkf(false, TEXT("%s"), *msg);}
			break;
			;
		}
	}
public:
#if WITH_EDITOR
	static void ShowEditorPopupAndStopPIE(const FString& Msg)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Msg));
	}
#endif

private:
	// --- Generic fallback (assume valid) ---
	template<typename T>
	static bool IsInvalidValue(const T&) { return false; }

	// --- Specialize for pointer types ---
	template<typename T>
	static bool IsInvalidValue(T* ptr) { return ptr == nullptr; }

	// --- Specialize for bool ---
	static bool IsInvalidValue(const bool& value) { return !value; }

	static inline const char* FileNameFromPath(const char* path)
	{
		const char* file = strrchr(path, '/');
		return file ? file + 1 : path;
	}


	~FLogger() = default;

	
};


inline DEFINE_LOG_CATEGORY(FS_Log_Debug);
inline DEFINE_LOG_CATEGORY(FS_Log_Info);
inline DEFINE_LOG_CATEGORY(FS_Log_Warn);
inline DEFINE_LOG_CATEGORY(FS_Log_Error);
inline DEFINE_LOG_CATEGORY(FS_Log_Fatal);



// Macros for automatic file/line/expression capture

#if !UE_BUILD_SHIPPING
#define FS_HANDLE(expr, level) FLogger::Get().Handle((expr), level, #expr, __FILE__, __LINE__)
#define FS_HANDLE_OR(expr, fallback, level) FLogger::Get().Handle((expr),(fallback),level, #expr, __FILE__, __LINE__)
#define FS_HANDLE(expr, level) FLogger::Get().Handle((expr), level, #expr, __FILE__, __LINE__)

#define FS_DEBUG(x)  FLogger::Handle((x), FLoggerLevel::Debug, #x, __FILE__, __LINE__)
#define FS_INFO(x)   FLogger::Handle((x), FLoggerLevel::Info,  #x, __FILE__, __LINE__)
#define FS_WARN(x)   FLogger::Handle((x), FLoggerLevel::Warn,  #x, __FILE__, __LINE__)
#define FS_ERROR(x)  FLogger::Handle((x), FLoggerLevel::Error, #x, __FILE__, __LINE__)
#define FS_FATAL(x)  FLogger::Handle((x), FLoggerLevel::Fatal, #x, __FILE__, __LINE__)

#define FS_HANDLE_IF(expr) if(FS_HANDLE(expr, FLoggerLevel::Warn))
#define FS_HANDLE_MSG(x,level,msg) FLogger::HandleMsg((x), level, FString(msg), __FILE__, __LINE__)

#define FS_DEBUG_MSG(x, msg)  FLogger::HandleMsg((x), FLoggerLevel::Debug, FString(msg), __FILE__, __LINE__)
#define FS_INFO_MSG(x, msg)   FLogger::HandleMsg((x), FLoggerLevel::Info,  FString(msg), __FILE__, __LINE__)
#define FS_WARN_MSG(x, msg)   FLogger::HandleMsg((x), FLoggerLevel::Warn,  FString(msg), __FILE__, __LINE__)
#define FS_ERROR_MSG(x, msg)  FLogger::HandleMsg((x), FLoggerLevel::Error, FString(msg), __FILE__, __LINE__)
#define FS_FATAL_MSG(x, msg)  FLogger::HandleMsg((x), FLoggerLevel::Fatal, FString(msg), __FILE__, __LINE__)

#define FS_CHECK_PTR(ptr) \
if (!ptr.IsValid()) { GIS_FATAL_MSG(false, FString::Printf(TEXT("TSharedPtr '%s' is invalid! File: %s Line: %d"), TEXT(#ptr), ANSI_TO_TCHAR(__FILE__), __LINE__)); }


#define FS_PRINT_SCREEN(Text) FLogger::PrintScreen(Text);
#define FS_SHOW_POPUP(message) FLogger::ShowPopup(message);





#else
#define FS_HANDLE(expr, level) (expr) // compiled away
#define FS_HANDLE_OR(expr, fallback, level)(expr)
#define FS_HANDLE(expr, level) (expr)

#define FS_DEBUG(x) (x)
#define FS_INFO(x) (x)
#define FS_WARN(x) (x)
#define FS_ERROR(x) (x)
#define FS_FATAL(x) (x)

#define FS_HANDLE_IF(expr) (expr)
#define FS_HANDLE_MSG(x,level,msg) 

#define FS_DEBUG_MSG(x, msg)  (x)
#define FS_INFO_MSG(x, msg)   (x)
#define FS_WARN_MSG(x, msg)   (x)
#define FS_ERROR_MSG(x, msg)  (x)
#define FS_FATAL_MSG(x, msg)  (x)

#define FS_CHECK_PTR(ptr) (x)

#define FS_PRINT_SCREEN(Text) (;)
#define FS_SHOW_POPUP(message)
#endif

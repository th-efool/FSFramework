#pragma once

#include "CoreMinimal.h"
#include "Misc/MessageDialog.h"

#if WITH_EDITOR
#include "Editor.h"
#endif

//=============================================================================
// Log categories
//=============================================================================
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Debug, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Info, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Warn, Warning, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Error, Error, All);
DECLARE_LOG_CATEGORY_EXTERN(FS_Log_Fatal, Fatal, All);

//=============================================================================
// Severity
//=============================================================================
enum class EFSLogLevel : uint8
{
	Debug,
	Info,
	Warn,
	Error,
	Fatal
};

//=============================================================================
// Static class
//=============================================================================
class FSCORE_API FSLogger final
{
public:
	static inline bool bCrashOnFatal = true;
	static inline float DefaultScreenDuration = 5.0f;

	//-------------------------------------------------------------------------
	// Primary public API — pure static, no macros needed
	//-------------------------------------------------------------------------

	template<typename T>
	static T Check(const T& Value, EFSLogLevel Level)
	{
		return CheckInternal(Value, Level, TEXT("Validation failed"), __FILE__, __LINE__);
	}

	template<typename T>
	static T Check(const T& Value, EFSLogLevel Level, const FString& Message)
	{
		return CheckInternal(Value, Level, Message, __FILE__, __LINE__);
	}

	template<typename T, typename FuncType>
	static void ValidateIf(const T& Value, FuncType Func)
	{
		ValidateInternal(Value, Func, __FILE__, __LINE__);
	}

	static void Log(EFSLogLevel Level, const FString& Message)
	{
		LogInternal(Level, Message, __FILE__, __LINE__);
	}

	static void PrintScreen(const FString& Text, const FColor& Color = FColor::White, float Duration = DefaultScreenDuration)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Text);

		UE_LOG(FS_Log_Info, Display, TEXT("%s"), *Text);
	}

	//-------------------------------------------------------------------------
	// Overloads for simplicity
	//-------------------------------------------------------------------------
	template<typename... Args>
	static void Info(const TCHAR* Fmt, Args&&... args)
	{
		LogFormatted(EFSLogLevel::Info, Fmt, Forward<Args>(args)...);
	}

	template<typename... Args>
	static void Warn(const TCHAR* Fmt, Args&&... args)
	{
		LogFormatted(EFSLogLevel::Warn, Fmt, Forward<Args>(args)...);
	}

	template<typename... Args>
	static void Error(const TCHAR* Fmt, Args&&... args)
	{
		LogFormatted(EFSLogLevel::Error, Fmt, Forward<Args>(args)...);
	}

	template<typename... Args>
	static void Debug(const TCHAR* Fmt, Args&&... args)
	{
		LogFormatted(EFSLogLevel::Debug, Fmt, Forward<Args>(args)...);
	}

	template<typename... Args>
	static void Fatal(const TCHAR* Fmt, Args&&... args)
	{
		LogFormatted(EFSLogLevel::Fatal, Fmt, Forward<Args>(args)...);
	}

private:
	//-------------------------------------------------------------------------
	// Validation traits
	//-------------------------------------------------------------------------
	template<typename T> static bool IsInvalid(const T&) { return false; }
	template<typename T> static bool IsInvalid(T* Ptr) { return Ptr == nullptr; }
	static bool IsInvalid(std::nullptr_t) { return true; }
	template<typename T> static bool IsInvalid(const TSharedPtr<T>& Ptr) { return !Ptr.IsValid(); }
	template<typename T> static bool IsInvalid(const TWeakPtr<T>& Ptr) { return !Ptr.IsValid(); }
	template<typename T> static bool IsInvalid(const TWeakObjectPtr<T>& Ptr) { return !Ptr.IsValid(); }
	static bool IsInvalid(bool bVal) { return !bVal; }

	//-------------------------------------------------------------------------
	// Internals (all automatic source capture)
	//-------------------------------------------------------------------------
	template<typename T>
	static T CheckInternal(const T& Value, EFSLogLevel Level, const FString& Msg, const char* File, int32 Line)
	{
		if (IsInvalid(Value))
			LogMessage(Level, Msg, File, Line);
		return Value;
	}

	template<typename T, typename FuncType>
	static void ValidateInternal(const T& Value, FuncType Func, const char* File, int32 Line)
	{
		if (IsInvalid(Value))
			LogMessage(EFSLogLevel::Warn, TEXT("Validation failed"), File, Line);
		else
			Func(Value);
	}

	static void LogInternal(EFSLogLevel Level, const FString& Msg, const char* File, int32 Line)
	{
		LogMessage(Level, Msg, File, Line);
	}

	static void LogMessage(EFSLogLevel Level, const FString& Msg, const char* File, int32 Line)
	{
		const FString Formatted = FString::Printf(
			TEXT("[%s:%d] %s"),
			ANSI_TO_TCHAR(ExtractFileName(File)), Line, *Msg);
		LogWithLevel(Level, Formatted);
	}

	static void LogWithLevel(EFSLogLevel Level, const FString& Msg)
	{
		switch (Level)
		{
		case EFSLogLevel::Debug: UE_LOG(FS_Log_Debug, Log, TEXT("%s"), *Msg); break;
		case EFSLogLevel::Info:  UE_LOG(FS_Log_Info, Log, TEXT("%s"), *Msg); break;
		case EFSLogLevel::Warn:  UE_LOG(FS_Log_Warn, Warning, TEXT("%s"), *Msg); break;
		case EFSLogLevel::Error: UE_LOG(FS_Log_Error, Error, TEXT("%s"), *Msg); break;
		case EFSLogLevel::Fatal:
			UE_LOG(FS_Log_Fatal, Fatal, TEXT("%s"), *Msg);
			if (bCrashOnFatal)
				checkf(false, TEXT("%s"), *Msg);
			break;
		}
	}

	template<typename... Args>
	static void LogFormatted(EFSLogLevel Level, const TCHAR* Fmt, Args&&... args)
	{
		FString Msg = FString::Printf(Fmt, Forward<Args>(args)...);
		LogInternal(Level, Msg, __FILE__, __LINE__);
	}

	static const char* ExtractFileName(const char* Path)
	{
		const char* Slash = strrchr(Path, '/');
		if (!Slash) Slash = strrchr(Path, '\\');
		return Slash ? Slash + 1 : Path;
	}
};

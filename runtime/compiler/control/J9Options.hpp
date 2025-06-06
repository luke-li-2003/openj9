/*******************************************************************************
 * Copyright IBM Corp. and others 2000
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] https://openjdk.org/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0-only WITH Classpath-exception-2.0 OR GPL-2.0-only WITH OpenJDK-assembly-exception-1.0
 *******************************************************************************/

#ifndef J9_OPTIONS_INCL
#define J9_OPTIONS_INCL

/*
 * The following #define and typedef must appear before any #includes in this file
 */
#ifndef J9_OPTIONS_CONNECTOR
#define J9_OPTIONS_CONNECTOR
namespace J9 { class Options; }
namespace J9 { typedef J9::Options OptionsConnector; }
#endif

#include "control/OMROptions.hpp"

#include <stdint.h>
#include "control/OptionsUtil.hpp"
#include "env/jittypes.h"
#if defined(J9VM_OPT_JITSERVER)
namespace TR { class CompilationInfo; }
namespace TR { class CompilationInfoPerThreadBase; }
#endif /* defined(J9VM_OPT_JITSERVER) */

struct J9VMInitArgs;

namespace J9
{
/**
 * This enum and the associated string array _externalOptionsMetadata
 * in J9Options.cpp should be kept in sync.
 */
enum ExternalOptions
   {
   TR_FirstExternalOption                        = 0,
   Xnodfpbd                                      = 0,
   Xdfpbd                                        = 1,
   Xhysteresis                                   = 2,
   Xnoquickstart                                 = 3,
   Xquickstart                                   = 4,
   Xtuneelastic                                  = 5,
   XtlhPrefetch                                  = 6,
   XnotlhPrefetch                                = 7,
   Xlockword                                     = 8,
   XlockReservation                              = 9,
   XjniAcc                                       = 10,
   Xlp                                           = 11,
   Xlpcodecache                                  = 12,
   Xcodecache                                    = 13,
   Xcodecachetotal                               = 14,
   XXcodecachetotal                              = 15,
   XXplusPrintCodeCache                          = 16,
   XXminusPrintCodeCache                         = 17,
   XsamplingExpirationTime                       = 18,
   XcompilationThreads                           = 19,
   XaggressivenessLevel                          = 20,
   Xnoclassgc                                    = 21,
   Xjit                                          = 22,
   Xnojit                                        = 23,
   Xjitcolon                                     = 24,
   Xaot                                          = 25,
   Xnoaot                                        = 26,
   Xaotcolon                                     = 27,
   XXdeterministic                               = 28,
   XXplusRuntimeInstrumentation                  = 29,
   XXminusRuntimeInstrumentation                 = 30,
   XXplusPerfTool                                = 31,
   XXminusPerfTool                               = 32,
   XXdoNotProcessJitEnvVars                      = 33,
   XXplusMergeCompilerOptions                    = 34,
   XXminusMergeCompilerOptions                   = 35,
   XXLateSCCDisclaimTimeOption                   = 36,
   XXplusUseJITServerOption                      = 37,
   XXminusUseJITServerOption                     = 38,
   XXplusJITServerTechPreviewMessageOption       = 39,
   XXminusJITServerTechPreviewMessageOption      = 40,
   XXJITServerAddressOption                      = 41,
   XXJITServerPortOption                         = 42,
   XXJITServerTimeoutOption                      = 43,
   XXJITServerSSLKeyOption                       = 44,
   XXJITServerSSLCertOption                      = 45,
   XXJITServerSSLRootCertsOption                 = 46,
   XXplusJITServerUseAOTCacheOption              = 47,
   XXminusJITServerUseAOTCacheOption             = 48,
   XXplusRequireJITServerOption                  = 49,
   XXminusRequireJITServerOption                 = 50,
   XXplusJITServerLogConnections                 = 51,
   XXminusJITServerLogConnections                = 52,
   XXJITServerAOTmxOption                        = 53,
   XXplusJITServerLocalSyncCompilesOption        = 54,
   XXminusJITServerLocalSyncCompilesOption       = 55,
   XXplusMetricsServer                           = 56,
   XXminusMetricsServer                          = 57,
   XXJITServerMetricsPortOption                  = 58,
   XXJITServerMetricsSSLKeyOption                = 59,
   XXJITServerMetricsSSLCertOption               = 60,
   XXplusJITServerShareROMClassesOption          = 61,
   XXminusJITServerShareROMClassesOption         = 62,
   XXplusJITServerAOTCachePersistenceOption      = 63,
   XXminusJITServerAOTCachePersistenceOption     = 64,
   XXJITServerAOTCacheDirOption                  = 65,
   XXJITServerAOTCacheNameOption                 = 66,
   XXcodecachetotalMaxRAMPercentage              = 67,
   XXplusJITServerAOTCacheDelayMethodRelocation  = 68,
   XXminusJITServerAOTCacheDelayMethodRelocation = 69,
   XXplusIProfileDuringStartupPhase              = 70,
   XXminusIProfileDuringStartupPhase             = 71,
   XXplusJITServerAOTCacheIgnoreLocalSCC         = 72,
   XXminusJITServerAOTCacheIgnoreLocalSCC        = 73,
   XXplusHealthProbes                            = 74,
   XXminusHealthProbes                           = 75,
   XXJITServerHealthProbePortOption              = 76,
   XXplusTrackAOTDependencies                    = 77,
   XXminusTrackAOTDependencies                   = 78,
   XXplusJITServerUseProfileCache                = 79,
   XXminusJITServerUseProfileCache               = 80,
   TR_NumExternalOptions                         = 81
   };

/**
 * @brief This data structure is used to describe external JVM options that
 *        the JIT processes. An option is considered external if it is not part
 *        of the -Xjit or -Xaot flag. These options are found and/or consumed
 *        using FIND_AND_CONSUME_VMARG / FIND_ARG_IN_VMARGS.
 */
struct ExternalOptionsMetadata
   {
   /** @brief The external option string */
   const char * const _externalOption;

   /**
    * @brief The way an option should be matched when using
    *        FIND_AND_CONSUME_VMARG / FIND_ARG_IN_VMARGS. Can be one of the
    *        following:
    *        - EXACT_MATCH
    *        - STARTSWITH_MATCH
    *        - EXACT_MEMORY_MATCH
    *        - OPTIONAL_LIST_MATCH
    *        - OPTIONAL_LIST_MATCH_USING_EQUALS
    */
   const int8_t       _match;

   /** @brief The index into the args array of this option, if it exists. */
   int32_t            _argIndex;

   /**
    * @brief Indicates whether this option should be consumed by the JIT;
    *        every valid external option has to be consumed or the JVM will
    *        exit with an error when using
    *        -XX:-IgnoreUnrecognizedXXColonOptions. This just amounts to
    *        using FIND_AND_CONSUME_VMARG rather than FIND_ARG_IN_VMARGS.
    */
   const bool         _consumedByJIT;
   };

class OMR_EXTENSIBLE Options : public OMR::OptionsConnector
   {
   public:

   Options() : OMR::OptionsConnector() {}

   Options(TR_Memory * m,
           int32_t index,
           int32_t lineNumber,
           TR_ResolvedMethod *compilee,
           void *oldStartPC,
           TR_OptimizationPlan *optimizationPlan,
           bool isAOT=false,
           int32_t compThreadID=-1)
      : OMR::OptionsConnector(m,index,lineNumber,compilee,oldStartPC,optimizationPlan,isAOT,compThreadID)
      {}

   Options(TR::Options &other) : OMR::OptionsConnector(other) {}

   enum FSDInitStatus
      {
      FSDInit_Error,
      FSDInit_NotInitialized,
      FSDInit_Initialized
      };

   static FSDInitStatus _fsdInitStatus;

   static bool _doNotProcessEnvVars;

   static bool _reportByteCodeInfoAtCatchBlock;
   /** \brief
    *     Returns the _reportByteCodeInfoAtCatchBlock
    *
    *  \details
    *     reportByteCodeInfoAtCatchBlock defines whether Byte Code Information should be reported on a catch block.
    *
    */
   static inline bool getReportByteCodeInfoAtCatchBlock() { return _reportByteCodeInfoAtCatchBlock; }
   /** \brief
    *     Setter for _reportByteCodeInfoAtCatchBlock
    *
    */
   static inline bool setReportByteCodeInfoAtCatchBlock(bool b = true) { return _reportByteCodeInfoAtCatchBlock = b; }

   static int32_t _samplingFrequencyInIdleMode;
   static int32_t getSamplingFrequencyInIdleMode() {return _samplingFrequencyInIdleMode;}

#if defined(J9VM_OPT_JITSERVER)
   static int32_t _statisticsFrequency;
   static int32_t getStatisticsFrequency() {return _statisticsFrequency;}

   static uint32_t _compilationSequenceNumber;
#endif /* defined(J9VM_OPT_JITSERVER) */

   static int32_t _samplingFrequencyInDeepIdleMode;
   static int32_t getSamplingFrequencyInDeepIdleMode() {return _samplingFrequencyInDeepIdleMode;}

   static int32_t _highActiveThreadThreshold;
   static int32_t getHighActiveThreadThreshold() {return _highActiveThreadThreshold;}

   static int32_t _veryHighActiveThreadThreshold;
   static int32_t getVeryHighActiveThreadThreshold() {return _veryHighActiveThreadThreshold;}

   static int32_t _maxCheckcastProfiledClassTests;
   static int32_t getCheckcastMaxProfiledClassTests() {return _maxCheckcastProfiledClassTests;}

   static int32_t _maxOnsiteCacheSlotForInstanceOf;
   /** \brief
    *     Returns the _maxOnsiteCacheSlotForInstanceOf
    *
    *  \details
    *     maxOnsiteCacheSlotForInstanceOf node defines number of onsite cache slots to generate per site of instanceOf
    *     Set this value to 0 to disable generation of onsite cache test for instanceOf
    *
    */
   static int32_t getMaxOnsiteCacheSlotForInstanceOf() {return _maxOnsiteCacheSlotForInstanceOf;}
   /** \brief
    *     Setter for _maxOnsiteCacheSlotForInstanceOf
    *
    */
   static int32_t setMaxOnsiteCacheSlotForInstanceOf(int32_t m) {return _maxOnsiteCacheSlotForInstanceOf = m;}

   static int32_t _resetCountThreshold;

   static int32_t _scorchingSampleThreshold;
   static int32_t _conservativeScorchingSampleThreshold; // used when many CPUs

   static int32_t _upperBoundNumProcForScaling;
   static int32_t _lowerBoundNumProcForScaling;
   static int32_t _veryHotSampleThreshold;
   static int32_t _relaxedCompilationLimitsSampleThreshold;
   static int32_t _sampleThresholdVariationAllowance;
   static int32_t _cpuEntitlementForConservativeScorching;

   static int32_t _sampleHeartbeatInterval;
   static int32_t getSamplingHeartbeatInterval() { return _sampleHeartbeatInterval;}

   static int32_t _sampleDontSwitchToProfilingThreshold;
   static int32_t _stackSize;
   static int32_t _profilerStackSize;
   static int32_t _smallMethodBytecodeSizeThreshold; // used on setting invocation counts
   static int32_t _smallMethodBytecodeSizeThresholdForCold; // used in GCR filtering
   static int32_t _smallMethodBytecodeSizeThresholdForJITServerAOTCache; // for determining which methods to convert to AOT done remotely

   static int32_t _countForMethodsCompiledDuringStartup;
   static int32_t getCountForMethodsCompiledDuringStartup() { return _countForMethodsCompiledDuringStartup; }

   static int32_t _countForLoopyBootstrapMethods;
   static int32_t _countForLooplessBootstrapMethods;
   static int32_t getCountForLoopyBootstrapMethods() { return _countForLoopyBootstrapMethods; }
   static int32_t getCountForLooplessBootstrapMethods() { return _countForLooplessBootstrapMethods; }

   // fast JNI option
   static TR::SimpleRegex *_jniAccelerator;
   static TR::SimpleRegex * getJniAccelerator() { return _jniAccelerator; }
   static void setJniAccelerator(TR::SimpleRegex *ja) { _jniAccelerator = ja; }

   static int32_t _classLoadingPhaseInterval;
   static int32_t _experimentalClassLoadPhaseInterval;
   static int32_t _classLoadingPhaseThreshold;
   static int32_t _classLoadingPhaseVariance;
   static int32_t _classLoadingRateAverage;
   static int32_t _secondaryClassLoadingPhaseThreshold;
   static int32_t _numClassLoadPhaseQuiesceIntervals;
   static int32_t _bigAppSampleThresholdAdjust; //shift value assigned to certain big app's ho and scorching threshold
   static int32_t _availableCPUPercentage;
   static int32_t _userClassLoadingPhaseThreshold;
   static bool _userClassLoadingPhase;

   static int32_t _cpuCompTimeExpensiveThreshold;
   int32_t getCpuCompTimeExpensiveThreshold() { return _cpuCompTimeExpensiveThreshold; }

   static uintptr_t _compThreadAffinityMask;
   static int32_t _interpreterSamplingThreshold;
   static int32_t _interpreterSamplingDivisor;
   static int32_t _interpreterSamplingThresholdInStartupMode;
   static int32_t _interpreterSamplingThresholdInJSR292;
   static int32_t _activeThreadsThreshold; // -1 means 'determine dynamically', 0 means feature disabled
   static int32_t _samplingThreadExpirationTime;
   static int32_t _compilationExpirationTime;
   static int32_t _compilationThreadPriorityCode; // a number between 0 and 4
   static int32_t _disableIProfilerClassUnloadThreshold;
   static int32_t _iprofilerReactivateThreshold;
   static int32_t _iprofilerIntToTotalSampleRatio;
   static int32_t _iprofilerSamplesBeforeTurningOff;
   static int32_t _iprofilerNumOutstandingBuffers;
   static int32_t _iprofilerBufferMaxPercentageToDiscard;
   static int32_t _iProfilerBufferInterarrivalTimeToExitDeepIdle; // ms
   static int32_t _iprofilerBufferSize; //iprofilerbuffer size in kb

   static int32_t _maxIprofilingCount; // when invocation count is larger than
                                       // this value Iprofiler will not collect data
   static int32_t _maxIprofilingCountInStartupMode; // same as above but value is used
                                                    // during STARTUP phase (and only during classLoadPhase)
   static int32_t _iprofilerFailRateThreshold; // will reactivate Iprofiler if failure rate exceeds this threshold
   static int32_t _iprofilerFailHistorySize;
   static int32_t _iprofilerFaninMethodMinSize; // minimum method size (in bytecodes) so that the method is
                                                // considered by the fanin mechanism in the inliner
   static int32_t _iProfilerMemoryConsumptionLimit;
   static int32_t _iProfilerBcHashTableSize;
   static int32_t _iProfilerMethodHashTableSize;
   static int32_t _IprofilerOffSubtractionFactor;
   static int32_t _IprofilerOffDivisionFactor;

   static int32_t _IprofilerPreCheckpointDropRate;

   static int32_t _LoopyMethodSubtractionFactor;
   static int32_t _LoopyMethodDivisionFactor;

   static int32_t _localCSEFrequencyThreshold;
   static int32_t _profileAllTheTime;
   static int32_t _seriousCompFailureThreshold; // above this threshold we generate a trace point in the Snap file
   static bool _useCPUsToDetermineMaxNumberOfCompThreadsToActivate;

   static int32_t _numCodeCachesToCreateAtStartup;
   static int32_t getNumCodeCachesToCreateAtStartup() { return _numCodeCachesToCreateAtStartup; }
   static bool _overrideCodecachetotal;
   static int32_t _dataCacheQuantumSize;
   static int32_t _dataCacheMinQuanta;
   static int32_t getDataCacheQuantumSize() { return _dataCacheQuantumSize; }
   static int32_t getDataCacheMinQuanta() { return _dataCacheMinQuanta; }

   static size_t _scratchSpaceLimitKBWhenLowVirtualMemory;
   static size_t getScratchSpaceLimitKBWhenLowVirtualMemory() { return _scratchSpaceLimitKBWhenLowVirtualMemory; }

   static int32_t _scratchSpaceFactorWhenJSR292Workload;
   static int32_t getScratchSpaceFactorWhenJSR292Workload() { return _scratchSpaceFactorWhenJSR292Workload; }

   static size_t _scratchSpaceLimitForHotCompilations; // Only used under -Xtune:throughput
   static size_t getScratchSpaceLimitForHotCompilations() { return _scratchSpaceLimitForHotCompilations; }

#if defined(J9VM_OPT_JITSERVER)
   static int32_t _scratchSpaceFactorWhenJITServerWorkload;
   static int32_t getScratchSpaceFactorWhenJITServerWorkload() { return _scratchSpaceFactorWhenJITServerWorkload; }
#endif /* defined(J9VM_OPT_JITSERVER) */

   static int32_t _lowVirtualMemoryMBThreshold;
   static int32_t getLowVirtualMemoryMBThreshold() { return _lowVirtualMemoryMBThreshold; }

   static int32_t _safeReservePhysicalMemoryValue;
   inline static int32_t getSafeReservePhysicalMemoryValue() { return _safeReservePhysicalMemoryValue; }
   inline static void setSafeReservePhysicalMemoryValue(int32_t size) { _safeReservePhysicalMemoryValue = size; }

   static int32_t _updateFreeMemoryMinPeriod;
   inline static int32_t getUpdateFreeMemoryMinPeriod() { return _updateFreeMemoryMinPeriod; }
   inline static void setUpdateFreeMemoryMinPeriod(int32_t value) { _updateFreeMemoryMinPeriod = value; }

   static int32_t _numDLTBufferMatchesToEagerlyIssueCompReq;
   static int32_t _dltPostponeThreshold;

   static int32_t _minSamplingPeriod;
   int32_t getMinSamplingPeriod() {return _minSamplingPeriod;}
   static int32_t _compilationBudget;

   static int32_t _compYieldStatsThreshold;
   static int32_t _compYieldStatsHeartbeatPeriod;
   static int32_t _numberOfUserClassesLoaded;
   static int32_t _numQueuedInvReqToDowngradeOptLevel;
   static int32_t _qszThresholdToDowngradeOptLevel;
   static int32_t _qsziThresholdToDowngradeDuringCLP;
   static int32_t _qszThresholdToDowngradeOptLevelDuringStartup;
   static int32_t _cpuUtilThresholdForStarvation;
   static int32_t _qszLimit; // maximum size of the compilation queue
   static int32_t _compPriorityQSZThreshold;
   static int32_t _GCRQueuedThresholdForCounting; // if too many GCR are queued we stop counting
   static int32_t _minimumSuperclassArraySize; //size of the minimum superclass array

   static int32_t _TLHPrefetchSize;
   static int32_t _TLHPrefetchLineSize;
   static int32_t _TLHPrefetchLineCount;
   static int32_t _TLHPrefetchStaggeredLineCount;
   static int32_t _TLHPrefetchBoundaryLineCount;
   static int32_t _TLHPrefetchTLHEndLineCount;
   static int32_t _numFirstTimeCompilationsToExitIdleMode; // use large number to disable the feature

#if defined(J9VM_OPT_JITSERVER)
   static int64_t _oldAge;
   static int64_t _oldAgeUnderLowMemory;
   static int64_t _timeBetweenPurges;
   static bool _shareROMClasses;
   static int32_t _sharedROMClassCacheNumPartitions;
   static int32_t _reconnectWaitTimeMs;
   static const uint32_t DEFAULT_JITCLIENT_TIMEOUT = 30000; // ms
   static const uint32_t DEFAULT_JITSERVER_TIMEOUT = 30000; // ms
   static int32_t _aotCachePersistenceMinDeltaMethods;
   static int32_t _aotCachePersistenceMinPeriodMs;
   static int32_t _jitserverMallocTrimInterval;
   static int32_t _lowCompDensityModeEnterThreshold;
   static int32_t _lowCompDensityModeExitThreshold;
   static int32_t _lowCompDensityModeExitLPQSize;
   static bool _aotCacheDisableGeneratedClassSupport;
   static TR::CompilationFilters *_JITServerAOTCacheStoreFilters;
   static TR::CompilationFilters *_JITServerAOTCacheLoadFilters;
   static TR::CompilationFilters *_JITServerRemoteExcludeFilters;
#endif /* defined(J9VM_OPT_JITSERVER) */

#if defined(J9VM_OPT_CRIU_SUPPORT)
   static int32_t _sleepMsBeforeCheckpoint;
#endif

   static int32_t _minTimeBetweenMemoryDisclaims; // ms
   static int32_t _mallocTrimPeriod; // seconds

   static int32_t _waitTimeToEnterIdleMode;
   static int32_t _waitTimeToEnterDeepIdleMode;
   static int32_t _waitTimeToExitStartupMode;
   static int32_t _waitTimeToGCR;
   static int32_t _waitTimeToStartIProfiler;
   static int32_t _compilationDelayTime;
   static int32_t _delayBeforeStateChange;

   static int32_t _invocationThresholdToTriggerLowPriComp; // we trigger an LPQ comp req only if the method
                                                           // was invoked at least this many times
   static int32_t _aotMethodThreshold;         // when number of methods found in shared cache exceeds this threshold
                                               // we stop AOTing new methods to be put in shared cache UNLESS
   static int32_t _aotMethodCompilesThreshold; // we have already AOT compiled at least this many methods
                                               //   complication due to zOS trade scenario: two JVMs share a cache
   static int32_t _aotWarmSCCThreshold; // if there are at least that many AOT bodies in SCC at startup
                                        // then we declare the SCC to be warm
   static int32_t _largeTranslationTime; // usec
   static int32_t _weightOfAOTLoad;
   static int32_t _weightOfJSR292;

   static int32_t _hwprofilerNumOutstandingBuffers;

   static TR_YesNoMaybe _hwProfilerEnabled;
   static TR_YesNoMaybe _perfToolEnabled;
   static uint32_t _hwprofilerHotOptLevelThreshold;
   static uint32_t _hwprofilerScorchingOptLevelThreshold;
   static uint32_t _hwprofilerWarmOptLevelThreshold;
   static uint32_t _hwprofilerReducedWarmOptLevelThreshold;
   static uint32_t _hwprofilerAOTWarmOptLevelThreshold;
   static uint32_t _hwprofilerLastOptLevel;
   static uint32_t _hwprofilerRecompilationInterval;
   static uint32_t _hwprofilerRIBufferPoolSize;
   static int32_t  _hwProfilerRIBufferProcessingFrequency;
   static int32_t  _hwProfilerRecompFrequencyThreshold;
   static int32_t  _hwProfilerRecompDecisionWindow;
   static int32_t  _numDowngradesToTurnRION;
   static int32_t  _qszThresholdToTurnRION;
   static int32_t  _qszMaxThresholdToRIDowngrade;
   static int32_t  _qszMinThresholdToRIDowngrade;
   static int32_t  _hwProfilerBufferMaxPercentageToDiscard;

   static uint32_t _hwprofilerPRISamplingRate;

   static uint32_t _hwProfilerExpirationTime;

   static uint32_t _hwprofilerRIBufferThreshold;
   static uint32_t _hwprofilerZRIBufferSize;
   static uint32_t _hwprofilerZRIMode;
   static uint32_t _hwprofilerZRIRGS;
   static uint32_t _hwprofilerZRISF;

   static int32_t _expensiveCompWeight; // weight of a comp request to be considered expensive
   static int32_t _jProfilingEnablementSampleThreshold;

   static bool _aggressiveLockReservation;

   static bool _xrsSync;

   static ExternalOptionsMetadata _externalOptionsMetadata[ExternalOptions::TR_NumExternalOptions];

   /**
    * @brief This static method iterates over the _externalOptionsMetadata table
    *        to find (and possibly consume) the string indicated by
    *        _externalOption, as well as updates the _argIndex with the
    *        index into the args array of the external option if it exists (-1
    *        otherwise).
    *
    * @param vm The J9JavaVM pointer
    * @param consume Specifies whether to use FIND_AND_CONSUME_VMARG or
    *                FIND_ARG_IN_VMARGS; default value is true
    */
   static void findExternalOptions(J9JavaVM *vm, bool consume = true);

   /**
    * @brief Returns the string associated with the ExternalOptions option
    *
    * @param option The ExternalOptions enum representing the external option
    *
    * @return The string associated with the ExternalOptions option
    */
   static const char * getExternalOptionString(ExternalOptions option)
      { return _externalOptionsMetadata[option]._externalOption; }

   /**
    * @brief Returns the index into the args array of the ExternalOptions option
    *
    * @param option The ExternalOptions enum representing the external option
    *
    * @return The cached arg index
    */
   static int32_t getExternalOptionIndex(ExternalOptions option)
      { return _externalOptionsMetadata[option]._argIndex; }

   static int8_t getExternalOptionMatch(ExternalOptions option)
      { return _externalOptionsMetadata[option]._match; }

   static void  printPID();






   static const char *kcaOffsets(const char *option, void *, TR::OptionTable *entry);

   static const char *gcOnResolveOption(const char *option, void *, TR::OptionTable *entry);

   static const char *tprofOption(const char *option, void *, TR::OptionTable *entry);

   static const char *loadLimitOption(const char *option, void *, TR::OptionTable *entry);

   static const char *loadLimitfileOption(const char *option, void *, TR::OptionTable *entry);

#if defined(J9VM_OPT_JITSERVER)
   static const char *JITServerAOTCacheStoreLimitOption(const char *option, void *, TR::OptionTable *entry);
   static const char *JITServerAOTCacheLoadLimitOption(const char *option, void *, TR::OptionTable *entry);
   static const char *JITServerRemoteExclude(const char *option, void *base, TR::OptionTable *entry);
   static bool JITServerParseCommonOptions(J9VMInitArgs *vmArgsArray, J9JavaVM *vm, TR::CompilationInfo *compInfo, bool postRestore = false);
   static void JITServerParseLocalSyncCompiles(J9VMInitArgs *vmArgsArray, J9JavaVM *vm, TR::CompilationInfo *compInfo, bool isFSDEnabled, bool postRestore = false);
#endif /* defined(J9VM_OPT_JITSERVER) */

   static const char *vmStateOption(const char *option, void *, TR::OptionTable *entry);

   static const char *setJitConfigRuntimeFlag(const char *option, void *base, TR::OptionTable *entry);
   static const char *resetJitConfigRuntimeFlag(const char *option, void *base, TR::OptionTable *entry);
   static const char *setJitConfigNumericValue(const char *option, void *base, TR::OptionTable *entry);

   static bool useCompressedPointers();
   static const char *limitOption(const char *option, void *, TR::OptionTable *entry);
   static const char *inlinefileOption(const char *option, void *, TR::OptionTable *entry);
   static const char *limitfileOption(const char *option, void *, TR::OptionTable *entry);
   static const char *versionOption(const char *option, void *, TR::OptionTable *entry);

   /** \brief
    *    Set memory manager functions related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    */
   void preProcessMmf(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set compiler mode.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    */
   void preProcessMode(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set JNI related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessJniAccelerator(J9JavaVM *vm);

   /** \brief
    *     Increase code cache total size based on codecachetotal options.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    */
   void preProcessCodeCacheIncreaseTotalSize(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set print code cache usage option.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessCodeCachePrintCodeCache(J9JavaVM *vm);

   /** \brief
    *     Set large code page size and flags.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    *
    *  \return true if successfully processed large code page size and flags.
    */
   bool preProcessCodeCacheXlpCodeCache(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set code cache related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    *
    *  \return true if successfully processed code cache related
    */
   bool preProcessCodeCache(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set sampling thread expiration time.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessSamplingExpirationTime(J9JavaVM *vm);

   /** \brief
    *     Set number of usable compilation threads.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    */
   void preProcessCompilationThreads(J9JavaVM *vm, J9JITConfig *jitConfig);

   /** \brief
    *     Set thread local heap related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessTLHPrefetch(J9JavaVM *vm);

   /** \brief
    *     Set hardware profiler related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessHwProfiler(J9JavaVM *vm);

   /** \brief
    *     Set deterministic mode related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    */
   void preProcessDeterministicMode(J9JavaVM *vm);

   /** \brief
    *     Set jit server related configuration.
    *
    *  \param vm
    *     J9JavaVM pointer.
    *
    *  \param jitConfig
    *     J9JITConfig pointer.
    *
    *  \return true if successfully set jit server related configuration.
    */
   bool preProcessJitServer(J9JavaVM *vm, J9JITConfig *jitConfig);

   bool  fePreProcess(void *base);
   bool  fePostProcessAOT(void *base);
   bool  fePostProcessJIT(void *base);
   bool  feLatePostProcess(void *base, TR::OptionSet *optionSet);
   bool  showOptionsInEffect();
   bool  showPID();
   void openLogFiles(J9JITConfig *jitConfig);

   bool isFSDNeeded(J9JavaVM *javaVM, J9HookInterface **vmHooks);
   FSDInitStatus initializeFSDIfNeeded(J9JavaVM *javaVM, J9HookInterface **vmHooks, bool &doAOT);

   static bool disableMemoryDisclaimIfNeeded(J9JITConfig *jitConfig);

#if defined(J9VM_OPT_JITSERVER)
   void setupJITServerOptions();

   static std::string packOptions(const TR::Options *origOptions);
   static TR::Options *unpackOptions(char *clientOptions, size_t clientOptionsSize, TR::CompilationInfoPerThreadBase* compInfoPT,
                                    TR_J9VMBase *fe, TR_Memory *trMemory);
   static std::string packLogFile(TR::FILE *fp);
   int writeLogFileFromServer(const std::string& logFileContent);
   void setLogFileForClientOptions(int suffixNumber = 0);
   void closeLogFileForClientOptions();
#endif /* defined(J9VM_OPT_JITSERVER) */

#if defined(J9VM_OPT_CRIU_SUPPORT)
   /**
    * \brief Static method used to reset FSD post-restore
    *
    * \param vm the J9JavaVM
    * \param vmThread the J9VMThread
    * \param[out] doAOT a boolean to indicate whether AOT should be disabled
    *                   after the call to this method
    *
    * \return The FSDInitStatus indicating the FSD Status
    */
   static FSDInitStatus resetFSD(J9JavaVM *vm, J9VMThread *vmThread, bool &doAOT);

   /**
    * \brief Method to enable or disable FSD options for the given TR::Options
    *        object
    *
    * \param flag true results in FSD enabled; false results in FSD disabled.
    */
   void setFSDOptions(bool flag);

   /**
    * \brief Method to enable or disable FSD options for the given TR::Options
    *        and all subsets
    *
    * \param flag true results in FSD enabled; false results in FSD disabled.
    */
   void setFSDOptionsForAll(bool flag);
#endif /* defined(J9VM_OPT_CRIU_SUPPORT) */

   private:

#if defined(J9VM_OPT_JITSERVER)
   static const char *JITServerAOTCacheLimitOption(const char *option, void *base, TR::OptionTable *entry, TR::CompilationFilters *&filters, const char *optName);
#endif /* defined(J9VM_OPT_JITSERVER) */
   };

}

#if defined(J9VM_OPT_CRIU_SUPPORT)
uintptr_t initializeCompilerArgsPostRestore(J9JavaVM* vm, intptr_t argIndex, char** xCommandLineOptionsPtr, bool isXjit, bool mergeCompilerOptions);
#endif

#endif

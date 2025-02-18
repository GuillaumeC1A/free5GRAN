/*
 * Copyright 2020-2021 Telecom Paris
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */
/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "NR-RRC-Definitions"
 * 	`asn1c -gen-PER -fcompound-names -findirect-choice -no-gen-example`
 */

#ifndef	_UL_DCCH_MessageType_H_
#define	_UL_DCCH_MessageType_H_


#include "asn_application.h"

/* Including external dependencies */
#include "constr_CHOICE.h"
#include "constr_SEQUENCE.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum UL_DCCH_MessageType_PR {
	UL_DCCH_MessageType_PR_NOTHING,	/* No components present */
	UL_DCCH_MessageType_PR_c1,
	UL_DCCH_MessageType_PR_messageClassExtension
} UL_DCCH_MessageType_PR;
typedef enum UL_DCCH_MessageType__c1_PR {
	UL_DCCH_MessageType__c1_PR_NOTHING,	/* No components present */
	UL_DCCH_MessageType__c1_PR_measurementReport,
	UL_DCCH_MessageType__c1_PR_rrcReconfigurationComplete,
	UL_DCCH_MessageType__c1_PR_rrcSetupComplete,
	UL_DCCH_MessageType__c1_PR_rrcReestablishmentComplete,
	UL_DCCH_MessageType__c1_PR_rrcResumeComplete,
	UL_DCCH_MessageType__c1_PR_securityModeComplete,
	UL_DCCH_MessageType__c1_PR_securityModeFailure,
	UL_DCCH_MessageType__c1_PR_ulInformationTransfer,
	UL_DCCH_MessageType__c1_PR_locationMeasurementIndication,
	UL_DCCH_MessageType__c1_PR_ueCapabilityInformation,
	UL_DCCH_MessageType__c1_PR_counterCheckResponse,
	UL_DCCH_MessageType__c1_PR_ueAssistanceInformation,
	UL_DCCH_MessageType__c1_PR_failureInformation,
	UL_DCCH_MessageType__c1_PR_ulInformationTransferMRDC,
	UL_DCCH_MessageType__c1_PR_scgFailureInformation,
	UL_DCCH_MessageType__c1_PR_scgFailureInformationEUTRA
} UL_DCCH_MessageType__c1_PR;

/* Forward declarations */
struct MeasurementReport;
struct RRCReconfigurationComplete;
struct RRCSetupComplete;
struct RRCReestablishmentComplete;
struct RRCResumeComplete;
struct SecurityModeComplete;
struct SecurityModeFailure;
struct ULInformationTransfer;
struct LocationMeasurementIndication;
struct UECapabilityInformation;
struct CounterCheckResponse;
struct UEAssistanceInformation;
struct FailureInformation;
struct ULInformationTransferMRDC;
struct SCGFailureInformation;
struct SCGFailureInformationEUTRA;

/* UL-DCCH-MessageType */
typedef struct UL_DCCH_MessageType {
	UL_DCCH_MessageType_PR present;
	union UL_DCCH_MessageType_u {
		struct UL_DCCH_MessageType__c1 {
			UL_DCCH_MessageType__c1_PR present;
			union UL_DCCH_MessageType__c1_u {
				struct MeasurementReport	*measurementReport;
				struct RRCReconfigurationComplete	*rrcReconfigurationComplete;
				struct RRCSetupComplete	*rrcSetupComplete;
				struct RRCReestablishmentComplete	*rrcReestablishmentComplete;
				struct RRCResumeComplete	*rrcResumeComplete;
				struct SecurityModeComplete	*securityModeComplete;
				struct SecurityModeFailure	*securityModeFailure;
				struct ULInformationTransfer	*ulInformationTransfer;
				struct LocationMeasurementIndication	*locationMeasurementIndication;
				struct UECapabilityInformation	*ueCapabilityInformation;
				struct CounterCheckResponse	*counterCheckResponse;
				struct UEAssistanceInformation	*ueAssistanceInformation;
				struct FailureInformation	*failureInformation;
				struct ULInformationTransferMRDC	*ulInformationTransferMRDC;
				struct SCGFailureInformation	*scgFailureInformation;
				struct SCGFailureInformationEUTRA	*scgFailureInformationEUTRA;
			} choice;
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *c1;
		struct UL_DCCH_MessageType__messageClassExtension {
			
			/* Context for parsing across buffer boundaries */
			asn_struct_ctx_t _asn_ctx;
		} *messageClassExtension;
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} UL_DCCH_MessageType_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_UL_DCCH_MessageType;
extern asn_CHOICE_specifics_t asn_SPC_UL_DCCH_MessageType_specs_1;
extern asn_TYPE_member_t asn_MBR_UL_DCCH_MessageType_1[2];
extern asn_per_constraints_t asn_PER_type_UL_DCCH_MessageType_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "MeasurementReport.h"
#include "RRCReconfigurationComplete.h"
#include "RRCSetupComplete.h"
#include "RRCReestablishmentComplete.h"
#include "RRCResumeComplete.h"
#include "SecurityModeComplete.h"
#include "SecurityModeFailure.h"
#include "ULInformationTransfer.h"
#include "LocationMeasurementIndication.h"
#include "UECapabilityInformation.h"
#include "CounterCheckResponse.h"
#include "UEAssistanceInformation.h"
#include "FailureInformation.h"
#include "ULInformationTransferMRDC.h"
#include "SCGFailureInformation.h"
#include "SCGFailureInformationEUTRA.h"

#endif	/* _UL_DCCH_MessageType_H_ */
#include "asn_internal.h"

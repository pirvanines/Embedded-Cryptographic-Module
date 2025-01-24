/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
  /* USER CODE END Header */
  /* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "optiga/optiga_util.h"
#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal.h"
#include "optiga/pal/pal_os_timer.h"
#include "optiga/optiga_crypt.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

optiga_crypt_t* me_crypt = NULL;

uint8_t random_data_buffer[32];

uint8_t return_value = 0;

optiga_lib_status_t return_status;

optiga_util_t* me_util = NULL;

uint8_t _hash_context_buffer[OPTIGA_HASH_CONTEXT_LENGTH_SHA_256];

optiga_hash_context_t me_hash = {

		.context_buffer = _hash_context_buffer,

		.context_buffer_length = sizeof(_hash_context_buffer),

		.hash_algo = (uint8_t)OPTIGA_HASH_TYPE_SHA_256
};

uint8_t _v[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

hash_data_from_host_t hash_input = {
		.buffer = _v,
		.length = sizeof(_v)
};

uint8_t hash_output[32];

static volatile optiga_lib_status_t optiga_lib_status;

optiga_key_id_t optiga_key_id;
uint32_t time_taken = 0;
uint16_t optiga_oid;

optiga_rsa_encryption_scheme_t encryption_scheme;
uint8_t encrypted_message[128];
uint16_t encrypted_message_length = sizeof(encrypted_message);

uint8_t decrypted_message[150];
uint16_t decrypted_message_length = sizeof(decrypted_message);

public_key_from_host_t public_key_from_host;

const uint8_t message[] = { "Hardware Security" };

uint8_t public_key[150];
uint16_t public_key_length = sizeof(public_key);
const uint8_t E0FC_metadata[] = { 0x20, 0x06, 0xD0, 0x01, 0x00, 0xD3, 0x01, 0x00 };

struct _L7_data {
	uint8_t msg[512];

	uint8_t msg_dig0[32];
	uint8_t msg_dig1[32];

	uint8_t sig_dig0[128];
	uint8_t sig_dig1[128];

	uint8_t	RSA_enc[2048];
	uint8_t	RSA_dec[2048];
} L7_data;

struct _test {
	uint8_t data[512];

	uint8_t digest1[32];
	uint8_t digest2[32];
}test;

static void optiga_util_callback(void* context, optiga_lib_status_t return_status)
{
	optiga_lib_status = return_status;
}

static void optiga_crypt_callback(void* context, optiga_lib_status_t return_status)
{
	optiga_lib_status = return_status;
	if (NULL != context)
	{
		// callback to upper layer here
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM2_Init();
	/* USER CODE BEGIN 2 */

	me_util = optiga_util_create(0, optiga_util_callback, NULL);

	optiga_lib_status = OPTIGA_LIB_BUSY;

	return_status = optiga_util_open_application(me_util, 0);

	while (optiga_lib_status == OPTIGA_LIB_BUSY)
	{
		//Wait until the optiga_util_open_application is completed
	}

	me_crypt = optiga_crypt_create(0, optiga_crypt_callback, NULL);
	if (NULL == me_crypt)
	{
		// break;
	}

	// ============================================== Generate data and digest ==============================================

	hash_data_from_host_t to_hash;
	to_hash.buffer = (uint8_t*)&L7_data.msg;
	to_hash.length = 256;

	uint8_t(*hash_out)[32] = &L7_data.msg_dig0;
	uint8_t(*rnd_buff)[256] = &L7_data.msg;

	uint8_t rep = 2;

	while (rep--) {

		// ------------------------------ Initialize data block ----------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_random(me_crypt,
			OPTIGA_RNG_TYPE_TRNG,
			rnd_buff,
			256);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		// ------------------------------ Sign data with SHA256 ----------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_hash(me_crypt,
			OPTIGA_HASH_TYPE_SHA_256,
			OPTIGA_CRYPT_HOST_DATA,
			&to_hash,
			hash_out
		);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		// ------------------------- Next block of data to setup ----------------------------
		rnd_buff++;
		to_hash.buffer += 256;
		hash_out++;
	}

	// ============================================== Metadata to generate the private key ==============================================
	optiga_lib_status = OPTIGA_LIB_BUSY;
	optiga_oid = 0xE0FC;
	return_status = optiga_util_write_metadata(me_util,
		optiga_oid,
		E0FC_metadata,
		sizeof(E0FC_metadata));
	if (OPTIGA_LIB_SUCCESS != return_status)
	{
		// break;
	}

	while (OPTIGA_LIB_BUSY == optiga_lib_status)
	{
		//Wait until the operation is completed
	}

	// ============================================== Generate the private and public keys ==============================================
	optiga_lib_status = OPTIGA_LIB_BUSY;
	optiga_key_id = OPTIGA_KEY_ID_E0FC;

	return_status = optiga_crypt_rsa_generate_keypair(me_crypt,
		OPTIGA_RSA_KEY_1024_BIT_EXPONENTIAL,
		(uint8_t)(OPTIGA_KEY_USAGE_ENCRYPTION | OPTIGA_KEY_USAGE_SIGN),
		FALSE,
		&optiga_key_id,
		public_key,
		&public_key_length);

	if (OPTIGA_LIB_SUCCESS != return_status)
	{
		// break;
	}

	while (OPTIGA_LIB_BUSY == optiga_lib_status)
	{
		//Wait until the operation is completed
	}

	// ================================================ Sign the digest with private key ================================================
	uint8_t(*digest)[32] = &L7_data.msg_dig0;
	uint8_t* signature = L7_data.sig_dig0;
	uint16_t signature_length = sizeof(L7_data.sig_dig0);

	rep = 2;
	while (rep--)
	{
		optiga_lib_status = OPTIGA_LIB_BUSY;
		return_status = optiga_crypt_rsa_sign(me_crypt,
			OPTIGA_RSASSA_PKCS1_V15_SHA256,
			digest,
			32,
			OPTIGA_KEY_ID_E0FC,
			signature,
			&signature_length,
			0x0000
		);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		digest++;
		signature += 128;
	}
	// ============================================== Encrypt the message ==============================================
	// 
	// 
	// ------------------------------------ Initialize data ---------------------------------
	encryption_scheme = OPTIGA_RSAES_PKCS1_V15;
	public_key_from_host.public_key = public_key;
	public_key_from_host.length = public_key_length;
	public_key_from_host.key_type = (uint8_t)OPTIGA_RSA_KEY_1024_BIT_EXPONENTIAL;

	uint8_t* data_to_enc = &L7_data;
	uint32_t enc_len = 832;
	const uint32_t enc_qnt = 100;

	uint8_t* enc_data = &L7_data.RSA_enc;

	rep = 9;

	while (rep--) {

		// ------------------------ Encrypt the data with public key --------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_encrypt_message(me_crypt,
			encryption_scheme,
			data_to_enc,
			(enc_len > enc_qnt) ? enc_qnt : enc_len,
			NULL,
			0,
			OPTIGA_CRYPT_HOST_DATA,
			&public_key_from_host,
			enc_data,
			&encrypted_message_length);
		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}
		enc_len -= enc_qnt;
		data_to_enc += enc_qnt;
		enc_data += 128;
	}
	// ============================================== Data decryption ==============================================
	// 
	// 
	// ---------------------------- Initialize data for decryption ----------------------------
	uint8_t* dec_data = &L7_data.RSA_dec;
	uint32_t dec_qnt = 100;

	uint32_t dec_len = 100;

	enc_data = &L7_data.RSA_enc;

	rep = 9;

	while (rep--) {

		// ----------------------- Decrypt data using the public key --------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_decrypt_and_export(me_crypt,
			encryption_scheme,
			enc_data,
			128,
			NULL,
			0,
			optiga_key_id,
			dec_data,
			&dec_len);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		dec_data += dec_qnt;
		enc_data += 128;
	}


	// ============================================== Verify the signature with private key ==============================================

	digest = &L7_data.msg_dig0;
	signature = L7_data.sig_dig0;
	signature_length = sizeof(L7_data.sig_dig0);

	rep = 2;
	while (rep--)
	{
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_verify(me_crypt,
			OPTIGA_RSASSA_PKCS1_V15_SHA256,
			digest,
			32,
			signature,
			signature_length,
			OPTIGA_CRYPT_HOST_DATA,
			&public_key_from_host,
			0x0000);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the optiga_crypt_random operation is completed
		}

		digest++;
		signature += 128;
	}

	// ================================================ Modifying the message and check the signature ==============================================
	// ==================================================================== (1) ====================================================================
	to_hash.buffer = (uint8_t*)&test.data;
	to_hash.length = 256;

	hash_out = &test.digest1;
	uint16_t pos = 2;

	// ------------------- Copy the original data in test structure ----------------
	for (uint16_t index = 0; index < 512; index++)
	{
		test.data[index] = L7_data.msg[index];
	}

	// ------------------------------- Modify the data -----------------------------
	test.data[pos] = test.data[pos] ^ 0x01;

	// ============================== Calculate digest =============================
	rep = 2;
	while (rep--)
	{
		// ---------------------- Generate digest - SHA256 -------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_hash(me_crypt,
			OPTIGA_HASH_TYPE_SHA_256,
			OPTIGA_CRYPT_HOST_DATA,
			&to_hash,
			hash_out
		);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		// -------------------- Next block of data to setup -------------------------
		to_hash.buffer += 256;
		hash_out++;
	}

	// ============================= Check the signature ============================
	digest = &test.digest1;
	signature = &L7_data.sig_dig0;
	signature_length = sizeof(L7_data.sig_dig0);

	rep = 2;
	while (rep--)
	{
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_verify(me_crypt,
			OPTIGA_RSASSA_PKCS1_V15_SHA256,
			digest,
			32,
			signature,
			signature_length,
			OPTIGA_CRYPT_HOST_DATA,
			&public_key_from_host,
			0x0000);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the optiga_crypt_random operation is completed
		}

		digest++;
		signature += 128;
	}

	// ================================================ Modifying the message and check the signature ==============================================
	// ==================================================================== (2) ====================================================================
	to_hash.buffer = (uint8_t*)&test.data;
	to_hash.length = 256;

	hash_out = &test.digest1;

	uint16_t pos1 = 3;
	uint16_t pos2 = 9;
	uint16_t pos3 = 100;

	// --------------------- Data restoration for the next test --------------------
	test.data[pos] = test.data[pos] ^ 0x01;

	// ------------------------------- Modify the data -----------------------------
	uint8_t auxiliar;
	auxiliar = test.data[pos1];
	test.data[pos1] = test.data[pos2];
	test.data[pos2] = test.data[pos3];
	test.data[pos3] = auxiliar;

	// ============================== Calculate digest =============================
	rep = 2;
	while (rep--)
	{
		// ---------------------- Generate digest - SHA256 -------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_hash(me_crypt,
			OPTIGA_HASH_TYPE_SHA_256,
			OPTIGA_CRYPT_HOST_DATA,
			&to_hash,
			hash_out
		);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		// -------------------- Next block of data to setup -------------------------
		to_hash.buffer += 256;
		hash_out++;
	}

	// ============================= Check the signature =============================
	digest = &test.digest1;
	signature = &L7_data.sig_dig0;
	signature_length = sizeof(L7_data.sig_dig0);

	rep = 2;
	while (rep--)
	{
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_verify(me_crypt,
			OPTIGA_RSASSA_PKCS1_V15_SHA256,
			digest,
			32,
			signature,
			signature_length,
			OPTIGA_CRYPT_HOST_DATA,
			&public_key_from_host,
			0x0000);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the optiga_crypt_random operation is completed
		}

		digest++;
		signature += 128;
	}

	// ================================================ Modifying the message and check the signature ==============================================
	// ==================================================================== (3) ====================================================================
	to_hash.buffer = (uint8_t*)&test.data;
	to_hash.length = 256;

	hash_out = &test.digest1;

	uint16_t startPos = 19;

	// --------------------- Data restoration for the next test --------------------
	auxiliar = test.data[pos3];
	test.data[pos3] = test.data[pos2];
	test.data[pos2] = test.data[pos1];
	test.data[pos1] = auxiliar;

	// ------------------------------- Modify the data -----------------------------
	for (uint8_t index = startPos; index < startPos + 15; index++)
	{
		test.data[index] = 0;
	}

	// ============================== Calculate digest =============================
	rep = 2;
	while (rep--)
	{
		// ---------------------- Generate digest - SHA256 -------------------------
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_hash(me_crypt,
			OPTIGA_HASH_TYPE_SHA_256,
			OPTIGA_CRYPT_HOST_DATA,
			&to_hash,
			hash_out
		);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the operation is completed
		}

		// -------------------- Next block of data to setup -------------------------
		to_hash.buffer += 256;
		hash_out++;
	}

	// ============================= Check the signature =============================
	digest = &test.digest1;
	signature = &L7_data.sig_dig0;
	signature_length = sizeof(L7_data.sig_dig0);

	rep = 2;
	while (rep--)
	{
		optiga_lib_status = OPTIGA_LIB_BUSY;

		return_status = optiga_crypt_rsa_verify(me_crypt,
			OPTIGA_RSASSA_PKCS1_V15_SHA256,
			digest,
			32,
			signature,
			signature_length,
			OPTIGA_CRYPT_HOST_DATA,
			&public_key_from_host,
			0x0000);

		if (OPTIGA_LIB_SUCCESS != return_status)
		{
			// break;
		}

		while (OPTIGA_LIB_BUSY == optiga_lib_status)
		{
			//Wait until the optiga_crypt_random operation is completed
		}

		digest++;
		signature += 128;
	}

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{


		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 200;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

	/* USER CODE BEGIN I2C1_Init 0 */

	/* USER CODE END I2C1_Init 0 */

	/* USER CODE BEGIN I2C1_Init 1 */

	/* USER CODE END I2C1_Init 1 */
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 400000;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN I2C1_Init 2 */

	/* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 4294967295;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(DBG_GPIO_Port, DBG_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : DBG_Pin */
	GPIO_InitStruct.Pin = DBG_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DBG_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : RST_Pin */
	GPIO_InitStruct.Pin = RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : EN_Pin */
	GPIO_InitStruct.Pin = EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(EN_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	   /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

<?php
require 'vendor/autoload.php';

use GuzzleHttp\Client;
//AppId (clientId), tenantId y password
// Datos de tu App Registration
$tenantId = "<TENANT_ID>";
$clientId = "<CLIENT_ID>";
$clientSecret = "<CLIENT_SECRET>";

// Nombre del Key Vault y secreto
$keyVaultName = "<NOMBRE_KEYVAULT>";
$secretName = "client_certificate";

// Crear cliente HTTP
$client = new Client();

// 1️⃣ Obtener token OAuth2 de Azure AD
$response = $client->request('POST', "https://login.microsoftonline.com/$tenantId/oauth2/v2.0/token", [
    'form_params' => [
        'grant_type' => 'client_credentials',
        'client_id' => $clientId,
        'client_secret' => $clientSecret,
        'scope' => 'https://vault.azure.net/.default'
    ]
]);

$token = json_decode($response->getBody(), true)['access_token'];

// 2️⃣ Llamar a Key Vault para obtener el secreto
$response = $client->request('GET', "https://$keyVaultName.vault.azure.net/secrets/$secretName?api-version=7.4", [
    'headers' => [
        'Authorization' => "Bearer $token"
    ]
]);

$secret = json_decode($response->getBody(), true);

echo "El valor del secreto '$secretName' es: " . $secret['value'] . "\n";

import pytest
import requests

BASE_URL = "https://localhost:2443/redfish/v1"
USERNAME = "root"
PASSWORD = "0penBmc"

@pytest.fixture
def session_token():
    url = f"{BASE_URL}/SessionService/Sessions"
    payload = {"UserName": USERNAME, "Password": PASSWORD}
    headers = {"Content-Type": "application/json"}
    r = requests.post(url, json=payload, headers= headers, verify=False)
    print("AUTH DEBUG", r.status_code, r.text)
    assert r.status_code in (200,201), "Auth fail"
    token = r.headers.get("X-Auth-Token")

    return r.headers["X-Auth-Token"]

def test_auth(session_token):
    assert session_token is not None

def test_system_info(session_token):
    headers = {"X-Auth-Token": session_token}
    r = requests.get(f"{BASE_URL}/Systems/system", headers=headers, verify=False)
    assert r.status_code == 200
    data = r.json()
    assert "Status" in data
    assert "PowerState" in data


def test_power_control(session_token):
    headers = {"X-Auth-Token": session_token}
    url = f"{BASE_URL}/Systems/system/Actions/ComputerSystem.Reset"
    payload = {"ResetType": "On"}
    r = requests.post(url, json=payload, headers=headers, verify=False)
    assert r.status_code == 202

    r2 = requests.get(f"{BASE_URL}/Systems/system", headers=headers, verify=False)
    data = r2.json()
    assert data.get("PowerState") == "On"

def test_cpu_temp_redfish(session_token):
    headers = {"X-Auth-Token": session_token}
    url = f"{BASE_URL}/Thermal"
    r = requests.get(url, headers=headers, verify=False)
    assert r.status_code == 200
    data = r.json()
    for sensor in data.get("Temperatures", []):
        assert "ReadingCelsius" in sensor


def test_cpu_sensors_redfish_ipmi(session_token):
    headers = {"X-Auth-Token": session_token}
    url = f"{BASE_URL}/Sensors"
    r = requests.get(url, headers=headers, verify=False)
    assert r.status_code == 200
    data = r.json()
    assert "Members" in data
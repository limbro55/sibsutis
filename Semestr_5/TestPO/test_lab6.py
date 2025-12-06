from locust import HttpUser, task, between

BMC_IP = "localhost"
PORT = 2443
USERNAME = "root"
PASSWORD = "0penBmc"

BASE_URL = f"https://{BMC_IP}:{PORT}"


class OpenBMCUser(HttpUser):
    wait_time = between(1, 2)

    @task
    def system_info(self):
        self.client.get(
            "/redfish/v1/Systems/system",
            auth=(USERNAME, PASSWORD),
            verify=False,
            name="OpenBMC: System Info"
        )

    @task
    def power_state(self):
        self.client.get(
            "/redfish/v1/Systems/system",
            auth=(USERNAME, PASSWORD),
            verify=False,
            name="OpenBMC: Power State"
        )

class PublicAPIUser(HttpUser):
    wait_time = between(1, 2)

    @task
    def posts(self):
        self.client.get(
            "https://jsonplaceholder.typicode.com/posts",
            name="PublicAPI: Posts"
        )

    # --- Тест: погода ---
    @task
    def weather(self):
        self.client.get(
            "https://wttr.in/Novosibirsk?format=j1",
            name="PublicAPI: Weather"
        )

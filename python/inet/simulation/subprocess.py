import subprocess
import os

class SubprocessSimulationRunner:
    def __init__(self):
        pass

    def setup(self):
        pass

    def teardown(self):
        pass

    def run(self, simulation_run, args):
        simulation_config = simulation_run.simulation_config
        simulation_project = simulation_config.simulation_project
        working_directory = simulation_config.working_directory
        full_working_directory = simulation_project.get_full_path(working_directory)
        env = os.environ.copy()
        env["INET_ROOT"] = simulation_project.get_full_path(".")
        return subprocess.run(args, cwd=full_working_directory, capture_output=True, env=env)

subprocess_simulation_runner = SubprocessSimulationRunner()
subprocess_simulation_runner.setup()
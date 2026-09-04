FROM python:3.9-slim


WORKDIR /Repertoire_racine


RUN apt update && \
    apt install -y gcc g++ make libgomp1 \
    mpich libmpich-dev && \
    rm -rf /var/lib/apt/lists/*


ENV PYTHONPATH=/Repertoire_racine


RUN find . -type f -name "*.sh" -exec chmod +x {} \;
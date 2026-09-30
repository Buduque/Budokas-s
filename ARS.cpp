#include <iostream>
#include <string>
#include <memory>
#include <array>
#include <algorithm>

// Função avançada que executa um comando e RETORNA a resposta do terminal
std::string executarEObterSaida(const std::string& comando) {
    std::array<char, 128> buffer;
    std::string resultado;

    // No Windows, use _popen e _pclose no lugar de popen/pclose
    #ifdef _WIN32
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(comando.c_str(), "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(comando.c_str(), "r"), pclose);
    #endif

    if (!pipe) {
        return "ERRO_INTERNO_PIPE";
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        resultado += buffer.data();
    }

    // Remove quebras de linha e espaços extras no final
    while (!resultado.empty() && (resultado.back() == '\n' || resultado.back() == '\r' || resultado.back() == ' ')) {
        resultado.pop_back();
    }

    return resultado;
}

// Função principal de automação inteligente
void superAutonomoGit(const std::string& mensagemCommit) {
    std::cout << "🚀 Iniciando automação total do Git...\n\n";

    // 1. Verifica se a pasta atual é um repositório Git
    std::string statusRepo = executarEObterSaida("git rev-parse --is-inside-work-tree 2>&1");
    if (statusRepo != "true") {
        std::cerr << "❌ Erro: Este diretório não é um repositório Git ou o Git não está instalado.\n";
        return;
    }

    // 2. Detecta a branch atual automaticamente
    std::string branchAtual = executarEObterSaida("git branch --show-current");
    if (branchAtual.empty()) {
        std::cerr << "❌ Erro: Não foi possível determinar a branch atual (talvez o repositório esteja vazio).\n";
        return;
    }
    std::cout << "📌 Branch detectada automaticamente: [" << branchAtual << "]\n";

    // 3. Verifica se há modificações antes de fazer qualquer coisa
    std::string modificacoes = executarEObterSaida("git status --porcelain");
    if (modificacoes.empty()) {
        std::cout << "✨ Nada para commitar. O repositório já está limpo!\n";
        return;
    }

    // 4. Executa o git add .
    std::cout << "📦 Adicionando arquivos modificados...\n";
    executarEObterSaida("git add .");

    // 5. Executa o Commit
    std::cout << "📝 Criando commit com a mensagem: \"" << mensagemCommit << "\"\n";
    std::string comandoCommit = "git commit -m \"" + mensagemCommit + "\"";
    std::string resultadoCommit = executarEObterSaida(comandoCommit);
    std::cout << resultadoCommit << "\n";

    // 6. Faz o Push de forma inteligente
    std::cout << "📤 Enviando alterações para o servidor remoto...\n";
    std::string comandoPush = "git push origin " + branchAtual + " 2>&1";
    std::string resultadoPush = executarEObterSaida(comandoPush);

    // Analisa o texto de resposta do push para validar o sucesso
    if (resultadoPush.find("error:") != std::string::npos || resultadoPush.find("fatal:") != std::string::npos) {
        std::cerr << "❌ Falha crítica no Push! Detalhes do terminal:\n" << resultadoPush << "\n";
    } else {
        std::cout << "✅ Sucesso absoluto! Tudo sincronizado na branch " << branchAtual << ".\n";
    }
}

int main(int argc, char* argv[]) {
    std::string mensagem;

    // Se o usuário passou a mensagem via argumento do terminal (ex: ./meu_git "feat: novo login")
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            mensagem += argv[i];
            if (i < argc - 1) mensagem += " ";
        }
    } else {
        // Se não passou argumento, pede para digitar de forma amigável
        std::cout << "Insira a mensagem do commit: ";
        std::getline(std::cin, mensagem);
    }

    if (mensagem.empty()) {
        mensagem = "update: automacao c++ " + executarEObterSaida("date"); // Mensagem padrão caso fique em branco
    }

    superAutonomoGit(mensagem);
    return 0;
}
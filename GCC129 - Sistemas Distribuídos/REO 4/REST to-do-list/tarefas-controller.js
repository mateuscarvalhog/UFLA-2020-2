let Tarefas = require('./tarefas-model');

exports.buscarTarefa = function(req, res) {
    Tarefas.findById(req.params.id, function(err, tarefa) {
        if (err) {
            return next(err);
        }
        return res.send(tarefa)
    });
};

exports.excluirTarefa = function(req, res) {
    Tarefas.findByIdAndRemove(req.params.id, function(err, tarefa) {
        if(err) {
            return res.next(err);
        }
        res.send(tarefa);
    });
};

exports.atualizarTarefa = function(req, res) {
    Tarefas.findByIdAndUpdate(req.params.id, req.body, {new : true}, function(err, tarefa) {
        if(err) {
            return res.next(err);
        }
        res.send(tarefa);
    });
};

exports.cadastrarTarefa = function(req, res) {
    let tarefa = new Tarefas({
        descricao: req.body.descricao,
        prazo: req.body.prazo,
        completa: req.body.completa     
    })
    tarefa.save(function (err){
        if (err) {
            return next(err);
        }
    });
    res.send(tarefa);
};

exports.listarTarefas = function(req, res) {
    Tarefas.find({}, function (err, tarefas) {
        if (err) {
            return next(err);
        }
        return res.send(tarefas);
    });
};
-- Table: public.users

-- DROP TABLE IF EXISTS public.users;

CREATE TABLE IF NOT EXISTS public.users
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    name text COLLATE pg_catalog."default",
    surname text COLLATE pg_catalog."default",
    patronymic text COLLATE pg_catalog."default",
    CONSTRAINT users_pkey PRIMARY KEY (id)
);

INSERT INTO public.users(name, surname, patronymic) VALUES ('Алена', 'Логинова', 'Олеговна');
INSERT INTO public.users(name, surname, patronymic) VALUES ('Игорь', 'Тихомиров', 'Витальевич');
INSERT INTO public.users(name, surname, patronymic) VALUES ('Антон', 'Вахитов', 'Павлович');
INSERT INTO public.users(name, surname, patronymic) VALUES ('Константин', 'Пирогов', 'Ростиславович');


CREATE TABLE IF NOT EXISTS public.documents
(
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    doc_name text COLLATE pg_catalog."default",
    CONSTRAINT documents_pkey PRIMARY KEY (id)
);

INSERT INTO public.documents(doc_name) VALUES ('Документация о охране труда');
INSERT INTO public.documents(doc_name) VALUES ('Документация о эксплуатации ПК');
INSERT INTO public.documents(doc_name) VALUES ('Документация о организации рабочего места');
INSERT INTO public.documents(doc_name) VALUES ('Документация о правах потребителя');
INSERT INTO public.documents(doc_name) VALUES ('Документация о пожарной безопасности');


CREATE TABLE IF NOT EXISTS public.doc_check
(
    user_id integer,
    doc_id integer,
    id integer NOT NULL GENERATED ALWAYS AS IDENTITY ( INCREMENT 1 START 1 MINVALUE 1 MAXVALUE 2147483647 CACHE 1 ),
    CONSTRAINT doc_check_pkey PRIMARY KEY (id),
    CONSTRAINT unique_dic UNIQUE (doc_id),
    CONSTRAINT fkey_doc FOREIGN KEY (doc_id)
        REFERENCES public.documents (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
        NOT VALID,
    CONSTRAINT fkey_user FOREIGN KEY (user_id)
        REFERENCES public.users (id) MATCH SIMPLE
        ON UPDATE NO ACTION
        ON DELETE NO ACTION
        NOT VALID
);

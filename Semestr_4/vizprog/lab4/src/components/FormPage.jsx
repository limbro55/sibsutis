import React from "react";
import { Formik, Field, Form, FieldArray } from "formik";
import * as Yup from "yup";

const PersonSchema = Yup.object().shape({
  name: Yup.string().required("Обязательное поле"),
  age: Yup.number().required("Обязательное поле").min(0),
  email: Yup.string().email("Некорректный email").required("Обязательное поле"),
  pet: Yup.array().of(
    Yup.object().shape({
      name: Yup.string().required("Обязательное поле"),
      age: Yup.number().required("Обязательное поле").min(0),
    })
  ),
});

function FormPage({ addPerson }) {
  return (
    <div>
      <h2>Добавить человека</h2>
      <Formik
        initialValues={{ name: "", age: "", email: "", pet: [] }}
        validationSchema={PersonSchema}
        onSubmit={(values, { resetForm }) => {
          addPerson(values);
          resetForm();
        }}
      >
        {({ values, errors, touched }) => (
          <Form>
            <div>
              <label>Имя: </label>
              <Field name="name" />
              {touched.name && errors.name && <div>{errors.name}</div>}
            </div>

            <div>
              <label>Возраст: </label>
              <Field name="age" type="number" />
              {touched.age && errors.age && <div>{errors.age}</div>}
            </div>

            <div>
              <label>Email: </label>
              <Field name="email" />
              {touched.email && errors.email && <div>{errors.email}</div>}
            </div>

            <FieldArray name="pet">
              {({ push, remove }) => (
                <div>
                  <h4>Питомцы</h4>
                  {values.pet.map((_, index) => (
                    <div key={index}>
                      <Field name={`pet[${index}].name`} placeholder="Имя питомца" />
                      <Field name={`pet[${index}].age`} type="number" placeholder="Возраст" />
                      <button type="button" onClick={() => remove(index)}>Удалить</button>
                    </div>
                  ))}
                  <button type="button" onClick={() => push({ name: "", age: "" })}>
                    Добавить питомца
                  </button>
                </div>
              )}
            </FieldArray>

            <button type="submit">Сохранить</button>
          </Form>
        )}
      </Formik>
    </div>
  );
}

export default FormPage;
